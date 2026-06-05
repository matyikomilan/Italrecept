#include<iostream>
#include"Sztring.hpp"
#include"Hozzavalo_m.hpp"
#include"DinTomb.hpp"
#include"Recept.hpp"
#include"Adatbazis.hpp"
#include"Menu.hpp"
#include "memtrace.h"
#include "kivetelek.hpp"

// #define CPORTA

#ifdef CPORTA

/**
* @brief teszteli a Sztring osztalyt
*/
void TESZT_Sztring(){
   //konstruktorok es getterek tesztelese
   Sztring str1;
   std::cout << " Sztring str1;\nstr1 : " << str1  << "\tgetterel: " << str1.getStr() << "\tmerete = " << str1.getSize() << std::endl;   //operator<< -t is teszteltuk

   Sztring str2("str2");
   std::cout << "Sztring str2(\"str2\");\nstr2: " << str2 << "\tgetterel: " << str2.getStr() << "\tmerete = " << str2.getSize() << std::endl;

   Sztring str3(str2);
   std::cout << "Sztring str3(str2);\nstr3: " << str3 << "\tgetterel: " << str3.getStr() << "\tmerete = " << str3.getSize() << std::endl;

   //kiir()
   std::cout << "str2.kiir():\n";
   str2.kiir(std::cout);
   std::cout << std::endl;

   //operatotrok tesztelese
   Sztring str4;
   str4 = str2;
   std::cout << "Sztring str4; str4 = str2;\nstr4: " << str4 << "\tgetterel: " << str4.getStr() << "\tmerete = " << str4.getSize() << std::endl;

   Sztring str5("str5");
   std::cout << "str5: " << str5 << std::endl;
   if(str4 == str5){
      std::cout << str4 << "=" << str5 << std::endl;
   }
   else{
      std::cout << str4 << "!=" << str5 << std::endl;
   }
   if(str3 == str4){
      std::cout << str3 << "=" << str4 << std::endl;
   }
   else{
      std::cout << str3 << "!=" << str4 << std::endl;
   }

   Sztring str6("Betuzendo szoveg");
   for(size_t i=0; i<str6.getSize(); ++i){
      std::cout << "str6[" << i << "] = " << str6[i] << std::endl;
   }

   Sztring str7("str7");
   str7 += 'a';
   std::cout << "Sztring str7(\"str7\"); str7 += 'a';\nstr7 + 'a' = " << str7 << std::endl;

   //beolv()
   Sztring str8;
   std::cout << "str8.beolv()\nstr8: ";
   str8.beolv(std::cin);
   std::cout << "str8: " << str8 << std::endl;
}

/**
* @brief teszteli a Hozzavalo es szarmaztatott osztalyait
*/
void TESZT_hozzavalo_m(){
   //1. Folyadek, Szilard
   //konstruktorok, getterek tesztelese
   Folyadek* f1 = new Folyadek("narancsle");
   std::cout << "Folyadek f1;\nf1.getNev(): " << f1->getNev() << std::endl;
   Szilard* s1 = new Szilard("cukor");
   std::cout << "Szilard s1;\ns1.getNev(): " << s1->getNev() << std::endl;
   Folyadek* f2 = new Folyadek("viz");
   std::cout << "Folyadek f2(\"f2\");\nf2.getNev(): " << f2->getNev() <<std::endl;
   Szilard* s2 = new Szilard("s2");
   std::cout << "Szilard s2(\"s2\");\ns2.getNev(): " << s2->getNev() <<std::endl;
   f2->setNev("almale");
   std::cout << "f2.setNev(\"almale\");\nf2: " << f2->getNev() << "\n";

   //2. HozzavaloMennyiseg
   //konstruktorok, getterek
   //a default konstruktort nem teszteljuk, mert a getHozz() miatt hibat dobna ugye
   HozzavaloMennyiseg hm1(f2, 12);
   std::cout << "hm1.getHozz().getNev(): " << hm1.getHozz().getNev() << "\thm1.getMenny(): " << hm1.getMenny() << std::endl;
   HozzavaloMennyiseg hm2(hm1);
   std::cout << "HozzavaloMennyiseg hm2(hm1);\nhm2(hm1):\n";
   std::cout << "hm2.getHozz().getNev(): " << hm2.getHozz().getNev();
   std::cout << "\thm2.getMenny(): " << hm2.getMenny() << std::endl;

   //memoriafelszabaditas
   delete f1;
   delete s1;
   delete f2;
   delete s2;
}

/**
 * @brief teszteli a DinTomb osztalyt
 */
void TESZT_dintomb(){
   //letrehozunk 2db HozzavaloMennyiseget
   Folyadek* f1 = new Folyadek("vodka");
   HozzavaloMennyiseg hm1(f1, 100);
   Folyadek* f2 = new Folyadek("narancsle");
   HozzavaloMennyiseg hm2(f2, 400);
   //berakjuk egy dintombbe
   DinTomb<HozzavaloMennyiseg> dt_hm;
   dt_hm.push_back(hm1);
   dt_hm.push_back(hm2);
   //kiiras:
   std::cout << "dt_hm.getSize(): " << dt_hm.getSize() << std::endl;
   for (size_t i = 0; i < dt_hm.getSize(); ++i) {
      std::cout << "dt_hm[" << i << "]: " << dt_hm[i].getHozz().getNev() << ", " << dt_hm[i].getMenny() << std::endl;
   }

   //insert:
   Folyadek* f3 = new Folyadek("ananaszle");
   HozzavaloMennyiseg hm3(f3, 300);
   dt_hm.insert(1, hm3);
   std::cout << "Insert utan, dt_hm meret: " << dt_hm.getSize() << std::endl;
   for (size_t i = 0; i < dt_hm.getSize(); ++i) {
       std::cout << "dt_hm[" << i << "]: " << dt_hm[i].getHozz().getNev() << ", " << dt_hm[i].getMenny() << std::endl;
   }

   //torles:
   dt_hm.torol(1);
   std::cout << "Torles utan, dt_hm meret: " << dt_hm.getSize() << std::endl;
   for (size_t i = 0; i < dt_hm.getSize(); ++i) {
       std::cout << "dt_hm[" << i << "]: " << dt_hm[i].getHozz().getNev() << ", " << dt_hm[i].getMenny() << std::endl;
   }

   //operator=
   DinTomb<HozzavaloMennyiseg> dt_hm2 = dt_hm;
   std::cout << "dt_hm2 (masolat) meret: " << dt_hm2.getSize() << std::endl;
   for (size_t i = 0; i < dt_hm2.getSize(); ++i) {
      std::cout << "dt_hm2[" << i << "]: " << dt_hm2[i].getHozz().getNev() << ", " << dt_hm2[i].getMenny() << "\n";
   }

   //memoriafelszabaditas
   delete f1;
   delete f2;
   delete f3;
}

/**
* @brief teszteli a Recept osztalyt
*/
void TESZT_Recept(){
   Sztring r1neve("Recept_01");
   Sztring tipus1("Tipus_01");
   //letrehozunk 2db HozzavaloMennyiseget
   Folyadek* f1 = new Folyadek("rum");
   HozzavaloMennyiseg hm1(f1, 50);
   Szilard* s1 = new Szilard("cukor");
   HozzavaloMennyiseg hm2(s1, 2);
   //berakjuk egy dt-be
   DinTomb<HozzavaloMennyiseg> dt_hm;
   dt_hm.push_back(hm1);
   dt_hm.push_back(hm2);

   //Recept osszerakasa
   Recept r1(r1neve, tipus1, dt_hm);

   std::cout << "r1 neve: " << r1.getNev();
   std::cout << "\tr1 tipusa: " << r1.getTipus();
   std::cout << "\nr1 elemei:" << std::endl;
   for(size_t i=0; i<r1.getHozz().getSize(); ++i){
      std::cout << "r1[" << i << "]: " << r1.getHozz()[i].getHozz().getNev() << " - " << r1.getHozz()[i].getMenny() << std::endl;
   }

   //operator=
   Recept r2;
   r2 = r1;

   std::cout << "r2 neve: " << r2.getNev();
   std::cout << "\tr2 tipusa: " << r2.getTipus();
   std::cout << "\tr2 elemei:" << std::endl;
   for(size_t i=0; i<r2.getHozz().getSize(); ++i){
      std::cout << "r2[" << i << "]: " << r2.getHozz()[i].getHozz().getNev() << " - " << r2.getHozz()[i].getMenny() << std::endl;
   }

   //setterek
   std::cout << "setNev() -> Recept_03\nsetTipus() -> Tipus_03" << std::endl;
   Sztring rn3("Recept_03");
   Sztring rt3("Tipus_03");
   r2.setNev(rn3);
   r2.setTipus(rt3);

   std::cout << "r2 neve: " << r2.getNev();
   std::cout << "\tr2 tipusa: " << r2.getTipus();
   std::cout << "\tr2 elemei:" << std::endl;
   for(size_t i=0; i<r2.getHozz().getSize(); ++i){
      std::cout << "r2[" << i << "]: " << r2.getHozz()[i].getHozz().getNev() << " - " << r2.getHozz()[i].getMenny() << std::endl;
   }

   //memfelsz:
   delete f1;
   delete s1;
   std::cout << "sikeres recept teszt";
}

/**
* @brief teszteli a Fajlkezelo osztalyt
*/
void TESZT_fajlk(){
   //Hozzavalok es receptek elkeszitese
   //hozzavalok:
   DinTomb<Hozzavalo*> hozzk;
   hozzk.push_back(new Folyadek("rum"));
   hozzk.push_back(new Szilard("cukor"));
   hozzk.push_back(new Folyadek("citromle"));
   //std::cout << "hozzk elkleszult";
   //hozzmk:
   DinTomb<HozzavaloMennyiseg> hozzavalok;
   hozzavalok.push_back(HozzavaloMennyiseg(hozzk[0], 50));
   hozzavalok.push_back(HozzavaloMennyiseg(hozzk[1], 10));
   //std::cout << "hozzmk elkleszult";
   //recept:
   Recept r1("mojito", "koktel", hozzavalok);
   DinTomb<Recept> reck;
   reck.push_back(r1);
   //std::cout << "reck elkleszult";

   //mentes fajlba:
   Fajlkezelo fk;
   fk.hozzk_ment("TESZT_hozzk.txt", hozzk);
   fk.reck_ment("TESZT_reck.txt", reck);
   //std::cout << "sikeres mentes fajlba";

   //betoltes fajlbol:
   DinTomb<Hozzavalo*> hozzk_betolt = fk.hozzk_betolt("TESZT_hozzk.txt");
   //std::cout << "hozzavalok sikeresen beolvasva2";
   DinTomb<Recept> reck_betolt = fk.reck_betolt("TESZT_reck.txt", hozzk_betolt);
   //std::cout << "receptek sikeresen beolvasva";
   //kiiras:
   std::cout << "Betoltott receptek:\n";
   for (size_t i = 0; i < reck_betolt.getSize(); ++i) {
      std::cout << reck_betolt[i].getTipus() << ": " << reck_betolt[i].getNev() << std::endl;
      for (size_t j = 0; j < reck_betolt[i].getHozz().getSize(); ++j) {
         std::cout << "\t" << reck_betolt[i].getHozz()[j].getHozz().getNev() << ": " << reck_betolt[i].getHozz()[j].getMenny() << std::endl;
      }
   }

   //memoriafelszabadatias:
   for (size_t i = 0; i < hozzk.getSize(); ++i) {
       delete hozzk[i];
   }
   for (size_t i = 0; i < hozzk_betolt.getSize(); ++i) {
       delete hozzk_betolt[i];
   }
}

/**
* @brief teszteli az Adatbazis osztalyt
*/
void TESZT_adatb(){
   Adatbazis adatb;
   //fajlok betoltese:
   //fajlok elkeszitese:
   DinTomb<Hozzavalo*> hozzk;
   hozzk.push_back(new Folyadek("whiskey"));
   hozzk.push_back(new Szilard("cukor"));
   DinTomb<HozzavaloMennyiseg> hozzavalok;
   hozzavalok.push_back(HozzavaloMennyiseg(hozzk[0], 50));
   hozzavalok.push_back(HozzavaloMennyiseg(hozzk[1], 10));
   Recept r1("mojito", "koktel", hozzavalok);
   DinTomb<Recept> reck;
   reck.push_back(r1);
   Fajlkezelo fk;
   fk.hozzk_ment("TESZT_hozzk.txt", hozzk);
   fk.reck_ment("TESZT_reck.txt", reck);
   //betoltes:
   adatb.betolt("TESZT_reck.txt", "TESZT_hozzk.txt", "statikus_receptek.txt");
   //kiiras:
   for (size_t i = 0; i < adatb.getHozzk().getSize(); ++i) {
      std::cout << adatb.getHozzk()[i]->getNev() << std::endl;
   }
   std::cout << "receptek:\n";
   for (size_t i = 0; i < adatb.getReck().getSize(); ++i) {
      std::cout << adatb.getReck()[i].getNev() << " (" << adatb.getReck()[i].getTipus() << ")\n";
   }
   std::cout << "statikus receptek:\n" << adatb.getStat_reck() << std::endl;

   //hozz_add()
   Folyadek* uj_hozz = new Folyadek("citromle");
   adatb.hozz_add(uj_hozz);
   std::cout << "ujhozz hozzaadasa utan:\n";
   for (size_t i = 0; i < adatb.getHozzk().getSize(); ++i) {
      std::cout << adatb.getHozzk()[i]->getNev() << "\n";
   }

   //ujrecept:
   DinTomb<HozzavaloMennyiseg> uj_hozzm;
   uj_hozzm.push_back(HozzavaloMennyiseg(uj_hozz, 20));
   Recept uj_recept("recept", "koktel", uj_hozzm);
   adatb.rec_add(uj_recept);
   std::cout << "ujrec hozzaadasa utan:\n";
   for (size_t i = 0; i < adatb.getReck().getSize(); ++i) {
      std::cout << adatb.getReck()[i].getNev() << " (" << adatb.getReck()[i].getTipus() << ")\n";
   }

   //rectorl:
   adatb.rec_torl(0);
   std::cout << "rectorl utan:\n";
   for (size_t i = 0; i < adatb.getReck().getSize(); ++i) {
      std::cout << adatb.getReck()[i].getNev() << " (" << adatb.getReck()[i].getTipus() << ")\n";
   }

   //memfelsz
   for (size_t i = 0; i < hozzk.getSize(); ++i) {
      delete hozzk[i];
   }
}

/**
* @brief teszteli a Menu osztalyt
*/
//mivel a Jporta kicrashelt az inputos teszteknel, ezert kikommenteztem ahol bekeres van
void TESZT_menu(){
   Adatbazis adatb;
   Menu menu(&adatb);

   //az adatbazist meg kell tolteni, hogy tesztelheto legyen a menu, mert a menu aktivan hasznalja az adatbazist
   //szuksegesek a tesztelos txt-k

   adatb.betolt("TESZT_reck.txt", "TESZT_hozzk.txt", "statikus_receptek.txt");

   menu.fomenu(std::cout);

   //fomenupont
   int valasztottmenupont = 3; //.fo_menu_pont(std::cout, std::cin);
   std::cout << "valasztott menupont: " << valasztottmenupont << std::endl;

   //vissza
   //menu.vissza(std::cout, std::cin);

   //ujhozzavalo
   Hozzavalo* ujhozz = new Folyadek("ujhozz"); //menu.ujhozz(std::cout, std::cin);
   std::cout << "uj hozzavalo neve: " << ujhozz->getNev() << std::endl;

   //hozzavalo torlese
   int idx = 2; //menu.hozz_torl(std::cout, std::cin);
   std::cout << "valasztott index: " << idx << std::endl;
   std::cout << "index(0-12): ";

   //ujindex input
   int ujidx =  2;  //menu.ujidx(std::cout, std::cin, 12);
   std::cout << "ujidx: " << ujidx << std::endl;

   //uj mennyiseg
   double ujmenny = 32; //menu.ujmenny(std::cout, std::cin);
   std::cout << ujmenny << std::endl;

   //uj hozzmenny
   //DinTomb<HozzavaloMennyiseg> ujhozzmk = menu.ujhozzmk(std::cout, std::cin);
   //for(size_t i=0; i<ujhozzmk.getSize() ; ++i){
   //   std::cout << ujhozzmk.getTomb()[i].getHozz().getNev() << " - " << ujhozzmk[i].getMenny() << std::endl;
   //}

   //ujrecept
   //Recept ujrec = menu.ujrecept(std::cout, std::cin);
   //std::cout << ujrec.getNev() << ujrec.getTipus() << std::endl;
   //for(size_t i=0; i<ujrec.getHozz().getSize(); ++i){
   //   std::cout << ujrec.getHozz().getTomb()[i].getHozz().getNev() << " - " << ujrec.getHozz().getTomb()[i].getMenny() << std::endl;
   //}

   //recept torlese
   //size_t megegyidx = menu.rec_torl(std::cout, std::cin);
   //std::cout << "rectorl: " << megegyidx << std::endl;

   //kiirasok
   menu.hozzk_kiir(std::cout);
   //menu.rec_kiir(std::cout, std::cin);
   menu.reck_kiir(std::cout);
   menu.stat_reck_kiir(std::cout);

   ////memfelsz:
   //for (size_t i = 0; i < adatb.getHozzk().getSize(); ++i) {
   //   delete adatb.getHozzk()[i];
   //}
   delete ujhozz;
}

/**
* @brief teszteli az osszes lehetseges kivetelt
*/
void TESZT_kivetelek() {
   try {
      DinTomb<int> dt;
      dt[0]; // ervenytelen index
   } catch (const LogicError& e) {
      std::cout << "DinTomb ervenytelen index: "; e.what().kiir(std::cout); std::cout << std::endl;
   }

   try {
      Sztring s;
      std::cout << "csak egy entert nyomjon (Sztring(\"\"))\nstr: ";
      s.beolv(std::cin);
   } catch (const InvalidInputError& e) {
      std::cout << "Sztring beolvasasi hiba: "; e.what().kiir(std::cout); std::cout << std::endl;
   }

   try {
      Folyadek f;
      f.setNev(""); // ures nev
   } catch (const InvalidInputError& e) {
      std::cout << "Hozzavalo ures nev: "; e.what().kiir(std::cout); std::cout << std::endl;
   }

   try {
      Recept r;
      r.setNev(""); // ures nev
   } catch (const InvalidInputError& e) {
      std::cout << "Recept ures nev: "; e.what().kiir(std::cout); std::cout << std::endl;
   }

   try {
      Recept r;
      r.setTipus(""); // ures tipus
   } catch (const InvalidInputError& e) {
      std::cout << "Recept ures tipus: "; e.what().kiir(std::cout); std::cout << std::endl;
   }

   try {
      Fajlkezelo fk;
      fk.hozzk_betolt("nem_letezik.txt"); // Nem letezo fajl
   } catch (const FileError& e) {
      std::cout << "Fajlkezelo nem letezo fajl: "; e.what().kiir(std::cout); std::cout << std::endl;
   }

   try {
      Adatbazis adb;
      adb.hozz_torl(0); // ervenytelen index
   } catch (const LogicError& e) {
      std::cout << "Adatbazis ervenytelen hozzavalo torles: "; e.what().kiir(std::cout); std::cout << std::endl;
   }
}

int main() {
    try {   
        TESZT_Sztring();
        TESZT_hozzavalo_m();
        TESZT_dintomb();
        TESZT_Recept();
        TESZT_fajlk();
        TESZT_adatb();
        TESZT_menu();
        TESZT_kivetelek();
    } catch (const FileError& e) {
        std::cout << "Fajlkezelesi kivetel: ";
        e.what().kiir(std::cout);
        std::cout << std::endl;
        return 1;
    } catch (const BaseError& e) {
        std::cout << "Egyeb kivetel: ";
        e.what().kiir(std::cout);
        std::cout << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Ismeretlen kivetel!" << std::endl;
        return 1;
    }
    std::cout << "Minden teszt sikeresen lefutott!" << std::endl;
    return 0;
}

#endif


#ifndef CPORTA

/**
 * @brief A program fo fv-je normal mukodeshez
 */
int main(){
   //input es output stream:
   std::ostream& os = std::cout;
   std::istream& is = std::cin;

   //adatbazis es menu inicializalasa
   Adatbazis adatb;
   adatb.betolt("receptek.txt", "hozzavalok.txt", "statikus_receptek.txt");
   Menu menu(&adatb);

   //user-input valtozoja
   int valasztott_fomenupont = -1;

   //menuvezerles megvalositasa:
   while(valasztott_fomenupont != 0){
      try{
         //konzol tisztitasa
         std::system("cls");

         //fomenu megjelenitese es a menupont kivalasztasa
         menu.fomenu(os);
         valasztott_fomenupont = menu.fo_menu_pont(os, is);

         //megfelelo menupontba iranyitas
         switch (valasztott_fomenupont){
            //Receptek menupont
            case 1:{
               //kiirjuk az italokat tipusuk szerint csoportositva, es bekerjuk az indexet annak az italnak, amelyiknek a receptjere kivancsi a user
               std::system("cls");
               menu.reck_kiir(os);

               //a felhasznalo kivalasztja, hogy melyik recept hozzavaloira kivancsi, majd a valasztott ital hozzavaloit ("receptjet") megjelenitjuk
               menu.rec_kiir(os, is);

               menu.vissza(std::cout, std::cin);
               break;
            }

            //Hozzavalok menupont
            case 2:{
               //kilistazzuk a hozzavalokat
               std::system("cls");
               menu.hozzk_kiir(os);

               menu.vissza(os, is);
               break;
            }

            //uj recept felvetele menupont
            case 3:{
               //A felhasznalo megadja az uj recept adatait, majd beadjuk az uj receptet az adatbazisba
               std::system("cls");
               adatb.rec_add(menu.ujrecept(os, is));

               break;
            }

            //recept torlese menupont
            case 4:{
               //a felhasznalo kivalasztja a torleno recept indexet, majd toroljuk a receptet az adatbazisbol
               std::system("cls");
               int torlendoreceptidx = menu.rec_torl(os, is);
               if(torlendoreceptidx != -1){
                  adatb.rec_torl(torlendoreceptidx);
               }
               break;

            }

            //ujhozzavalo menupont
            case 5:{
               //bekerjuk a felhasznalotol a hozzavalo nevet, majd az adatbazishoz adjuk
               std::system("cls");
               Hozzavalo* ujhozz = menu.ujhozz(os, is);
               if(!adatb.hozz_add(ujhozz)){
                  delete ujhozz;
                  menu.vissza(os, is);
               }

               break;
            }

            //hozzavalo torlese menupont
            case 6:{
               //bekerjuk a torlendo hozzavalo (indexe)t, may toroljuk az adatbazisbol
               std::system("cls");
               int torlendoidx = menu.hozz_torl(os, is);
               if(torlendoidx != -1){
                  adatb.hozz_torl(torlendoidx);
               }

               break;

            }

            default:
               break;
         }
      }
      //elkapjuk a kiveteleket
      catch (const InvalidInputError& e){
         system("cls");
         os << "ervenytelen bemenet: ";
         e.what().kiir(os);
         os << "\nprobald ujra" << std::endl;
         menu.vissza(os, is);
         is.clear();
         is.ignore(10000, '\n');
      }
      catch(const FileError& e){
         system("cls");
         os << "fajlkezelesi hiba: ";
         e.what().kiir(os);
         return 1;
      }
      catch (const LogicError& e){
         system("cls");
         os << "logikai hiba: ";
         e.what().kiir(os);
         os << "probald ujra\n" << std::endl;
         menu.vissza(os, is);
         is.clear();
         is.ignore(10000, '\n');
      }
      catch (const BaseError& e){
         system("cls");
         os << "hiba: ";
         e.what().kiir(os);
         return 1;
      }
      //catch (...) {
      //    os << "Ismeretlen hiba tortent!" << std::endl;
      //    return 1;
      //}  
   }
   
   //Mentjuk az esetleg megvaltoztatott adatbazist fajlba, de ezt is hibakezelve kell, mert dobhat hibat ugye
   try{
      adatb.ment("receptek.txt", "hozzavalok.txt");
   }
   catch(const FileError& e){
      os << "adatmentes kozben hiba: ";
      e.what().kiir(os);
      return 1;
   }

   return 0;
}

#endif