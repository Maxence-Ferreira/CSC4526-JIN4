#pragma once

class Attack {
 private:
  double damage;
  double speed;
  double range;
  

 public:
  virtual ~Attack() = default;
  virtual void execute() = 0;  // Méthode pure virtuelle à implémenter dans les
                               // classes dérivées
};