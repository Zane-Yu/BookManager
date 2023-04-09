#include<iostream>
#include<string>
#include<thread>

#include "logger.h"
#include "load.h"
#include "BookManager.h"

#define MaxBorw 20 

using namespace bookmanager;


int main() {
	std::string user, choice, usn, psd;
	BookManager bm(0, 0);
	bm.init_data();

	while (1) {
		std::cout << ">> 1.Login  2.Enroll  3.Exit" << std::endl;
		std::cout << ">> Please choose: ";
		std::cin >> choice;
		if (choice == "1" || choice == "2") {
			std::cout << "1.Manager  2.Reader" << std::endl;
			std::cout << "Your identify: ";
			std::cin >> user;
			std::cout << "Your username: ";
			std::cin >> usn;
			std::cout << "Your password: ";
			std::cin >> psd;
			if (choice == "2") {
				bm.enroll(user, usn, psd);
				continue;
			}
			else {
				if (bm.login(user, usn, psd)) break;
				else continue;
			}
		}
		else if (choice == "3") {
			bm.exit();
			return 0;
		}
		else continue;
	}
	
	while (1) {
		std::cout << ">> Please enter your choice (H for help): ";
		std::cin >> choice;
		if (choice == "H" || choice == "h" || choice == "?") {
			std::cout << "1.LIST: show the book list" << std::endl;
			std::cout << "2.INFO: show the information of borrowers" << std::endl;
			std::cout << "3.BORW: borrow some books" << std::endl;
			std::cout << "4.RETU: return some books" << std::endl;
			std::cout << "5.ADDB: add some now books" << std::endl;
			std::cout << "6.DELE: delete some books" << std::endl;
			std::cout << "7.MODI: modify the information of some books" << std::endl;
			std::cout << "8.BACK: Go back to the login screen" << std::endl;
			std::cout << "9.EXIT: exit the system" << std::endl;
		}
		if (user == "2" && (choice == "5" || choice == "6" || choice == "7" ||
			choice == "ADDB" || choice == "DELE" || choice == "MODI")) {
			logger.error("Insufficient permissions");
			continue;
		}
		if (choice == "1" || choice == "LIST") bm.show_books();
		if (choice == "2" || choice == "INFO") bm.lend_info(usn);
		if (choice == "3" || choice == "BROW") bm.borrow_books(usn);
		if (choice == "4" || choice == "RETU") bm.return_books(usn);
		if (choice == "5" || choice == "ADDB") bm.add_books();
		if (choice == "6" || choice == "DELE") bm.del_books();
		if (choice == "7" || choice == "MODI") bm.mod_info();
		if (choice == "8" || choice == "BACK") {
			bm.save_data();
			bm.screen(user, usn);
		}
		if (choice == "9" || choice == "EXIT") {
			bm.exit();
			break;
		}
	}

	system("pause");
	return 0;
}