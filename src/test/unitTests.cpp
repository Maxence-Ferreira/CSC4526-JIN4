#include <gtest/gtest.h>

#include <random>
#include <string>

#include "building/Archer.h"
#include "enemy/Cyrano.h"
#include "map/BeginPath.h"
#include "map/EndPath.h"
#include "map/Ground.h"
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
 * @details Ce test unitaire vérifie la cohérence globale de la génération
 * procédurale du terrain. Il s'assure qu'en utilisant une seed fixe
 * (reproductible), l'algorithme crée un réseau de cases routières (Path)
 * totalement connecté, sans aucune rupture (pas de cul-de-sac ni de cases
 * orphelines). Le test simule le parcours complet depuis chaque entrée
 * (BeginPath) jusqu'à la sortie (EndPath) pour prouver que l'algorithme de
 * Dijkstra (repath) a pu lier toutes les cases entre elles.
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
 * @details Ce test valide la justesse mathématique de l'algorithme de calcul
 * d'itinéraire (Dijkstra). En isolant la logique de la génération aléatoire, on
 * construit un mini-graphe fixe contenant une intersection offrant deux choix :
 * un raccourci direct et un long détour. Le test vérifie d'une part que les
 * pointeurs de direction (m_next) s'orientent vers le chemin le plus court, et
 * d'autre part qu'aucune boucle infinie n'est créée lors du chaînage des cases.
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
 * @details Ce test unitaire sécurise les règles de déplacement géométrique sur
 * la grille. Il met à l'épreuve la validation des connexions lors de l'appel à
 * addNeighbor(). On vérifie que le système accepte uniquement les voisins
 * adjacents (haut, bas, gauche, droite), et qu'il rejette strictement les
 * tentatives de connexions invalides : les déplacements en diagonale, les
 * téléportations sur des cases trop lointaines, l'auto-connexion d'une case sur
 * elle-même, ainsi que la duplication de voisins déjà enregistrés.
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
 * @details Ce test unitaire contrôle le gestionnaire de présence des entités
 * sur le chemin. Il garantit que chaque case Path maintient un registre exact
 * et en temps réel des ennemis qui l'occupent. Le test valide le cycle de vie
 * d'une présence : la case doit être initialement vide, détecter positivement
 * l'ennemi dès son ajout (hasEntity/getEntity), et nettoyer instantanément sa
 * mémoire lors de son retrait (changement de case ou mort de l'ennemi) afin
 * d'éviter le ciblage de "cibles fantômes".
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

/**
 * @brief Test 1 : La mort et le nettoyage de la carte (Critique anti-crash)
 * @details Si un ennemi meurt mais "oublie" de se retirer de la case sur
 * laquelle il se trouve, tes tours vont continuer de tirer sur un fantôme, ou
 * le jeu va crasher en essayant de lire ses coordonnées. Ce test s'assure qu'un
 * ennemi mort est correctement supprimé de son Path.
 */
TEST(EnemyTest, TakeDamageAndCleanUpPathOnDeath) {
  BeginPath startTile(0, 0);
  // On utilise Cyrano (500 PV de base)
  Cyrano e(&startTile);

  // Vérification initiale
  EXPECT_TRUE(e.isAlive());
  EXPECT_TRUE(startTile.hasEntity())
      << "L'ennemi ne s'est pas inscrit au spawn.";

  // Dégâts partiels (Il a 500 PV, on lui en enlève 400)
  e.takeDamage(400);
  EXPECT_TRUE(e.isAlive());

  // Coup fatal (On enlève 100 PV de plus)
  e.takeDamage(100);
  EXPECT_FALSE(e.isAlive()) << "Cyrano devrait etre mort (0 PV).";

  // VERIFICATION CRITIQUE
  EXPECT_FALSE(startTile.hasEntity())
      << "DANGER: L'ennemi est mort mais est reste sur la case.";
}

/**
 * @brief Test 2 : Le franchissement de case (Critique déplacement)
 * @details S'assure que la logique de mouvement (ratio, distance) fonctionne.
 * Quand l'ennemi parcourt la distance requise, il doit physiquement passer
 * son pointeur sur la case suivante et se désinscrire de la précédente.
 */
TEST(EnemyTest, MovementTransitionsToNextPath) {
  BeginPath start(0, 0);
  EndPath end(1, 0);
  start.addNeighbor(&end);
  end.update({});  // Lance Dijkstra

  Cyrano e(&start);

  EXPECT_TRUE(start.hasEntity());
  EXPECT_FALSE(end.hasEntity());

  // Cyrano a une vitesse de 0.0005 cases par ms.
  // Pour parcourir 1 case entière, il lui faut 2000 ms.
  // On simule 2500 ms pour être large et sûr qu'il traverse.
  e.move(2500);

  // Vérification de la transition
  EXPECT_FALSE(start.hasEntity()) << "Cyrano n'a pas quitte la premiere case.";
  EXPECT_TRUE(end.hasEntity())
      << "Cyrano n'est pas arrive sur la deuxieme case.";
}

/**
 * @brief Test 3 : Le temps de recharge (Critique gameplay)
 * @details S'assure que l'ennemi ne se transforme pas en "mitraillette".
 * Il doit être physiquement incapable de générer une attaque si son
 * chronomètre de rechargement (cooldown) n'est pas écoulé.
 */
TEST(EnemyTest, AttackRespectsCooldown) {
  BeginPath start(0, 0);
  Cyrano e(&start);  // Cyrano a un cooldown de 1000.0 ms

  Ground targetTile(0, 1);
  Archer dummyTarget(&targetTile, 100);  // Tour archer générique à 100 pièces

  // 1ère tentative : Le tir doit partir (le cooldown est initialement à 0)
  Attack* firstAttack = e.attacking(&dummyTarget);
  EXPECT_NE(firstAttack, nullptr) << "La premiere attaque n'est pas partie.";

  // 2ème tentative immédiate : Doit échouer car il recharge
  Attack* blockedAttack = e.attacking(&dummyTarget);
  EXPECT_EQ(blockedAttack, nullptr)
      << "Cyrano a tire 2 fois de suite sans respecter le cooldown !";

  // On crée un contexte vide (le C++ mettra des 0 et des nullptr partout par
  // défaut)
  context fauxCtx{};

  // On assigne uniquement ce dont le test a besoin
  fauxCtx.dt = 1001;
  fauxCtx.rand = std::make_unique<std::mt19937>(42);

  // On appelle update pour que Cyrano décrémente son currentCooldown
  e.update(fauxCtx);

  // 3ème tentative : Le temps est écoulé, le tir doit repartir
  Attack* thirdAttack = e.attacking(&dummyTarget);
  EXPECT_NE(thirdAttack, nullptr)
      << "Le cooldown est fini mais Cyrano ne tire toujours pas.";
}

/**
 * @brief Test 1 : Destruction du bâtiment (Critique anti-invincibilité)
 * @details S'assure que le bâtiment enregistre correctement les dégâts et
 * passe bien à l'état "mort" quand ses points de vie tombent à zéro.
 * Vital pour que le EnemyManager ou BuildingManager puisse nettoyer la carte.
 */
TEST(BuildingTest, TakeDamageAndDie) {
  Ground g(0, 0);
  Archer tower(&g, 100);  // Un archer a 1000 PV de base selon ton constructeur

  // Vérification initiale
  EXPECT_TRUE(tower.isAlive()) << "La tour devrait etre en vie a sa creation.";

  // Dégâts partiels
  tower.takeDamage(900);
  EXPECT_TRUE(tower.isAlive()) << "La tour devrait survivre avec 100 PV.";

  // Coup fatal
  tower.takeDamage(100);
  EXPECT_FALSE(tower.isAlive()) << "La tour devrait etre detruite (0 PV).";
}

/**
 * @brief Test 2 : Le Radar et la détection (Critique IA)
 * @details S'assure que la tour scrute correctement les chemins environnants.
 * Elle ne doit cibler une case QUE si celle-ci est dans sa portée ET 
 * qu'elle contient un ennemi. Elle doit ignorer les cases vides ou lointaines.
 */
TEST(BuildingTest, RadarDetectsEnemyOnPath) {
    Ground g(0, 0);
    Archer tower(&g, 100); // L'archer a une portée (range) de 3 cases
    
    Path farPath(0, 10);   // Case beaucoup trop loin (distance 10)
    Path closePath(0, 2);  // Case à portée (distance 2)

    // On simule le lien que le Terrain crée normalement au début du jeu
    farPath.addDistanceFrom(&tower);
    closePath.addDistanceFrom(&tower);

    // --- LE GENERATEUR ALEATOIRE REQUIS PAR TA NOUVELLE METHODE ---
    std::mt19937 fakeRand(42);

    // 1. Les deux chemins sont vides, la tour ne doit rien cibler
    EXPECT_EQ(tower.setTarget(fakeRand), nullptr) << "La tour cible une case vide !";

    // 2. On ajoute un ennemi sur le chemin hors de portée
    Cyrano farEnemy(&farPath); 
    EXPECT_EQ(tower.setTarget(fakeRand), nullptr) << "La tour cible un ennemi hors de sa portee !";

    // 3. On ajoute un ennemi sur le chemin à portée
    Cyrano closeEnemy(&closePath);
    
    // 1. L'ennemi s'est-il bien inscrit sur la case ?
    EXPECT_TRUE(closePath.hasEntity()) << "ERREUR 1 : L'ennemi n'a pas ete enregistre sur closePath !";
    
    // 2. La tour trouve-t-elle au moins une cible ?
    Tile* target = tower.setTarget(fakeRand);
    EXPECT_NE(target, nullptr) << "ERREUR 2 : La tour renvoie NULL ! (Soit m_tracked_path est vide, soit Archer::setTarget n'est pas appele).";
    
    // 3. Est-ce la bonne cible ?
    EXPECT_EQ(target, &closePath) << "ERREUR 3 : La tour a cible une autre case que prevu !";
  }

/**
 * @brief Test 3 : Le respect de la cadence de tir (Critique équilibrage)
 * @details S'assure que le bâtiment ne génère pas de projectiles en continu.
 * Si le temps de recharge (cooldown) n'est pas écoulé, la méthode d'attaque
 * doit être verrouillée.
 */
TEST(BuildingTest, AttackRespectsCooldown) {
  Ground g(0, 0);
  Archer tower(&g, 100);  // L'archer a un temps de recharge de 1000 ms

  Path targetPath(0, 1);  // La case visée

  // 1ère tentative : Le tir doit partir (cooldown à 0 au départ)
  Attack* firstAttack = tower.attacking(&targetPath);
  EXPECT_NE(firstAttack, nullptr)
      << "La premiere attaque de la tour n'est pas partie.";

  // 2ème tentative immédiate : Doit être bloquée !
  Attack* blockedAttack = tower.attacking(&targetPath);
  EXPECT_EQ(blockedAttack, nullptr)
      << "La tour a tire en rafale sans respecter son cooldown !";

// On crée un contexte vide (le C++ mettra des 0 et des nullptr partout par défaut)
    context fauxCtx{}; 
    
    // On assigne uniquement ce dont le test a besoin
    fauxCtx.dt = 1001;
    fauxCtx.rand = std::make_unique<std::mt19937>(42);

  // La tour met à jour son chronomètre interne
  tower.update(fauxCtx);

  // 3ème tentative : Le temps est écoulé, le tir doit repartir
  Attack* thirdAttack = tower.attacking(&targetPath);
  EXPECT_NE(thirdAttack, nullptr)
      << "Le cooldown est fini mais la tour ne tire toujours pas.";
}