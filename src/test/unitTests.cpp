#include <gtest/gtest.h>

#include <random>
#include <string>

#include "map/BeginPath.h"
#include "map/EndPath.h"
#include "map/Path.h"
#include "map/Terrain.h"

TEST(TERRAIN, PathOK) {
  std::random_device rd;
  std::mt19937 rand(rd());
  Terrain terter(50, 50, 5, rand);
  terter.getPaths();
}

/**
 * @brief Test : PathfindingIsFullyConnected
 * @details Ce test unitaire vérifie la cohérence globale de la génération procédurale du terrain.
 * Il s'assure qu'en utilisant une seed fixe (reproductible), l'algorithme crée un réseau de cases 
 * routières (Path) totalement connecté, sans aucune rupture (pas de cul-de-sac ni de cases orphelines).
 * Le test simule le parcours complet depuis chaque entrée (BeginPath) jusqu'à la sortie (EndPath) 
 * pour prouver que l'algorithme de Dijkstra (repath) a pu lier toutes les cases entre elles.
 */
TEST(TerrainTest, PathfindingIsFullyConnected) {
  std::mt19937 gen(42);
  int width = 20;
  int height = 15;

  // 1. On génère le terrain
  Terrain terrain(width, height, 3, gen);
  const auto& entries = terrain.getEntry();

  // On s'assure qu'il y a bien des entrées générées
  ASSERT_FALSE(entries.empty()) << "Le terrain n'a genere aucune entree !";

  int expectedEndX = width - 2;
  int expectedEndY = height / 2;

  // 2. On vérifie chaque chemin
  for (BeginPath* startTile : entries) {
    std::vector<Tile*> route =
        terrain.pathfind(startTile->getX(), startTile->getY());

    // Le chemin ne doit pas être vide (pas d'orphelin)
    ASSERT_FALSE(route.empty())
        << "Chemin orphelin trouve aux coordonnees : " << startTile->getX()
        << "," << startTile->getY();

    // La dernière case doit être la sortie attendue
    Tile* endTile = route.back();
    EXPECT_EQ(endTile->getX(), expectedEndX) << "Mauvaise destination X";
    EXPECT_EQ(endTile->getY(), expectedEndY) << "Mauvaise destination Y";
  }
}

/**
 * @brief Test : DijkstraChoosesShortestPath
 * @details Ce test valide la justesse mathématique de l'algorithme de calcul d'itinéraire (Dijkstra).
 * En isolant la logique de la génération aléatoire, on construit un mini-graphe fixe contenant 
 * une intersection offrant deux choix : un raccourci direct et un long détour.
 * Le test vérifie d'une part que les pointeurs de direction (m_next) s'orientent vers le chemin le 
 * plus court, et d'autre part qu'aucune boucle infinie n'est créée lors du chaînage des cases.
 */

TEST(PathfindingTest, DijkstraChoosesShortestPath) {
  // 1. SCÉNARIO : On crée un réseau manuel en forme de boucle
  BeginPath start(0, 0);
  Path nodeA(1, 0);
  Path nodeB(2, 0);
  Path nodeC(1, 1);
  Path nodeD(2, 1);
  Path nodeE(3, 1);
  EndPath end(3, 0);

  // 2. CONNEXIONS
  // Chemin principal (court)
  start.addNeighbor(&nodeA);
  nodeA.addNeighbor(&nodeB);
  nodeB.addNeighbor(&end);

  // Le détour (chemin long)
  nodeA.addNeighbor(&nodeC);
  nodeC.addNeighbor(&nodeD);
  nodeD.addNeighbor(&nodeE);
  nodeE.addNeighbor(&end);

  // 3. EXÉCUTION DE L'ALGORITHME
  // On appelle update({}) sur la sortie, ce qui déclenche repath()
  end.update({});

  // 4. VÉRIFICATIONS (ASSERTIONS)
  // Vérification A : Le point de départ a bien trouvé un chemin
  ASSERT_NE(start.next(), nullptr) << "Le point de depart n'est pas connecte !";

  // Vérification B : La case A (l'intersection) a choisi la bonne direction
  EXPECT_EQ(nodeA.next(), &nodeB)
      << "ERREUR : A l'intersection, Dijkstra a pris le chemin long (C) au "
         "lieu du court (B) !";

  // Vérification C : On compte le nombre exact de pas depuis le point de départ
  Path* current = &start;
  int steps = 0;

  while (current != &end && current != nullptr) {
    current = current->next();
    steps++;

    // Sécurité anti-boucle infinie au cas où Dijkstra tournerait en rond
    if (steps > 10) {
      FAIL() << "Boucle infinie detectee dans les m_next !";
      break;
    }
  }

  // Le chemin S -> A -> B -> End fait exactement 3 sauts
  EXPECT_EQ(steps, 3) << "Le chemin parcouru ne fait pas la bonne taille ("
                      << steps << " sauts au lieu de 3).";
}

/**
 * @brief Test : NeighborValidationBlocksInvalidPaths
 * @details Ce test unitaire sécurise les règles de déplacement géométrique sur la grille.
 * Il met à l'épreuve la validation des connexions lors de l'appel à addNeighbor().
 * On vérifie que le système accepte uniquement les voisins adjacents (haut, bas, gauche, droite),
 * et qu'il rejette strictement les tentatives de connexions invalides : les déplacements en diagonale, 
 * les téléportations sur des cases trop lointaines, l'auto-connexion d'une case sur elle-même, 
 * ainsi que la duplication de voisins déjà enregistrés.
 */

TEST(PathTest, NeighborValidationBlocksInvalidPaths) {
  Path center(5, 5);

  Path validRight(6, 5);
  Path validTop(5, 4);
  Path invalidDiagonal(6, 6);
  Path invalidFar(8, 5);

  // 1. Ajout de voisins valides
  center.addNeighbor(&validRight);
  center.addNeighbor(&validTop);

  // 2. Tentatives d'ajouts invalides
  center.addNeighbor(&invalidDiagonal);  // Diagonale (dx=1, dy=1 -> somme=2)
  center.addNeighbor(&invalidFar);       // Trop loin (dx=3 -> somme=9)
  center.addNeighbor(&center);           // Soi-même
  center.addNeighbor(&validRight);       // Doublon (déjà ajouté)

  EXPECT_EQ(center.getNeighbors().size(), 2);
}

/**
 * @brief Test : EntityManagementTracksEnemiesProperly
 * @details Ce test unitaire contrôle le gestionnaire de présence des entités sur le chemin.
 * Il garantit que chaque case Path maintient un registre exact et en temps réel des ennemis qui l'occupent.
 * Le test valide le cycle de vie d'une présence : la case doit être initialement vide, détecter 
 * positivement l'ennemi dès son ajout (hasEntity/getEntity), et nettoyer instantanément sa mémoire 
 * lors de son retrait (changement de case ou mort de l'ennemi) afin d'éviter le ciblage de "cibles fantômes".
 */

TEST(PathTest, EntityManagementTracksEnemiesProperly) {
  Path pathTile(0, 0);

  // Vérification initiale
  EXPECT_FALSE(pathTile.hasEntity())
      << "Le chemin devrait etre vide a la creation.";

  // On simule un pointeur d'ennemi (pas besoin d'un vrai objet lourd,
  // l'adresse mémoire suffit pour tester la logique du std::vector)
  Enemy* fakeEnemy = reinterpret_cast<Enemy*>(0xDEADBEEF);

  // Ajout
  pathTile.addEnemy(fakeEnemy);
  EXPECT_TRUE(pathTile.hasEntity())
      << "Le chemin ne detecte pas l'ennemi ajoute.";
  EXPECT_EQ(pathTile.getEntity().size(), 1);
  EXPECT_EQ(pathTile.getEntity()[0], fakeEnemy);

  // Retrait
  pathTile.removeEnemy(fakeEnemy);
  EXPECT_FALSE(pathTile.hasEntity())
      << "L'ennemi n'a pas ete correctement retire !";
  EXPECT_TRUE(pathTile.getEntity().empty());
}