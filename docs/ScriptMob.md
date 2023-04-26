# Scripte Mob
<br />
Le script de jeu comprend toutes les information du gamplay, chaque vague de mob, l'ordre dans lequel ils a

## Mob

| # | ty | hp | dp | sp | sh | ap |
| :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: |
| Description | Type of skin mob | Healthpoint | Dammage by shoot | Speed mob | Speed Shoot | Auto aim the players |
| Example | 1 - 5 | 200 - 2000 | 5 - 50 | 1 - 10 | 1 - 10 | True - False |


## Game Play

| # | WD | R |
| :------------: | :------------: | :------------: |
| Description | Wait until all mobs on the map are dead before launching the next wave of mobs | Replace value by random data |

WD Creates a new wave which are automatically counted by the client.<br />
T By default an attack is launched every 2ms, if 2 attack launch at same time, use T_0.<br />
R Random data is within a range of values.<br />
TAB is key used to separate instructions from each other, several in a row are allowed.<br />

## Range Values

| # | PS | NB | HP | SP | SM | DV | A_NBR | T |
| :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: |
| Range value | Undefined | 1 - 5 | 250 - 2000 | Undefined | 0 - 8 | -45 - 45 | 40 - 80 & 25 - 50 & -45 - 45 | 0 - 5000 |

PS -> Skin de zbir random<br />
NB -> Si la valeur n'est pas set par défaut il n'y en a qu'un<br />
HP -> A redefinir en fonction du DPS player<br />
SP -> A définir en fonction de l'echelle choisie<br />
SM -> pour une vitesse = 0 les mob ne bougerons pas<br />
DV -> Si SM = 0 alors on peut ne pas définir DV<br />

Mob par défaut :
    - Spaw milieu de l'ecran
    - Vecteur de déplacement horozontale
    - Vie 1/4 celle du player
    - Dammage 1/8 du montant max de la vie du joueur
    - Speed shoot 3 fois celle du mob
    - Tire horizontale

### Exemple
PS_R	NB_10	HP_250	SM_1	SP_R,R	DV_AP,AP	A1_20,10,AP,AP	A1	A1	A1	A1	A1	A1	A1	A1	A1<br />
WD<br />
PS_StartBoss.png	NB_1	HP_2000	SP_50,50	SM_0	A1_40,25,0,0	A2_40,25,AP,AP	A1	T_50	A2	A2	A1	A2<br />

## Class Mobs and Attacks

```cpp
    class attack {
        private:
            int _nbr;
            int _dammage;
            int _speed;
            std::pair<int, int> _dir;
        public:
            attack(int nbr){_nbr = nbr;};
            ~attack();
            void setDammage(int dammage){_dammage = dammage;};
            void setSpeed(int speed){_speed = speed;};
            void setDir(int x, int y){_dir = std::make_pair(x, y);};
            int getDammage(){return _dammage;};
            int getSpeed(){return _speed;};
            std::pair<int, int> getDir(){return _dir;};
            attack get_attack(){return *this;};
    };

    class mob {
        private:
            std::string _ps; // path sprite
            int _nbr; // number of mob
            int _hp; // health point
            std::pair<int, int> _sp; //spawn point
            std::pair<int, int> _dv; //direction vector
            int _sm; // speed
            std::map<int, attack> _attacks; // attack
        public:
            mob();
            ~mob();
            void setPs(std::string ps){_ps = ps;};
            void setNbr(int nbr){_nbr = nbr;};
            void setHp(int hp){_hp = hp;};
            void setSp(int x, int y){_sp = std::make_pair(x, y);};
            void setDv(int x, int y){_dv = std::make_pair(x, y);};
            void setSm(int sm){_sm = sm;};
            void setAttacks(attack atk);
    };
```