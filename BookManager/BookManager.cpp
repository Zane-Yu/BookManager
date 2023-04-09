#include "BookManager.h"

using namespace bookmanager;

void BookManager::screen(std::string &user, std::string &usn) {
	load.info("Conversion");
	while (1) {
		std::string psd, choice;
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
				this->enroll(user, usn, psd);
				continue;
			}
			else {
				if (this->login(user, usn, psd)) break;
				else continue;
			}
		}
		else if (choice == "3") {
			load.info("Back");
			this->save_data();
			return;
		}
		else continue;
	}
}


bool BookManager::login(std::string user, std::string usn, std::string psd) {
	for (int i = 0; i < _usn_psd.size(); ++i) {
		if (_usn_psd[i]._user==user && _usn_psd[i]._usn == usn && _usn_psd[i]._psd == psd) {
			load.info("Load");
			return true;
		}
	}
	logger.error("The account number or password is incorrect");
	return false;
}

void BookManager::enroll(std::string user, std::string usn, std::string psd) {
	for (int i = 0; i < _usn_psd.size(); ++i) {
		if (_usn_psd[i]._usn == usn) {
			logger.warn("The user has existed");
			return;
		}
	}
	_usn_psd.push_back({ user, usn, psd });
	this->save_data();
}

void BookManager::add_books() {
	std::cout << "-->> How many books you want to add: ";
	std::cin >> _choice;
	if (_choice == "q" || _choice == "Q") return;
	int addNum = std::stoi(_choice);
	if (addNum > 0) {
		int no; std::string name; std::string author; int num; bool stat; std::string t;
		for (int i = 0; i < addNum; ++i) {
			std::cout << "-->> Book id: ";       std::cin >> no;
			std::cout << "-->> Book name: ";     std::cin >> name;
			std::cout << "-->> Author name: ";   std::cin >> author;
			std::cout << "-->> How many: ";      std::cin >> num;
			std::cout << "-->> Can be borrowed: "; std::cin >> stat;

			book_info bi(no, name, author, num, stat, logger.get_tiem());
			_book_shelf.push_back(bi);
		}
		_type_num += addNum;
	}
	this->save_data();
}

void BookManager::show_books() {
	if (_book_shelf.size() == 0) {
		logger.warn("The book shelf is empty");
		return;
	}
	std::cout << std::string(66, '-') << std::endl;
	std::cout << std::setw(8) << "No." << std::setw(16) << "Title" << std::setw(12) << "Author";
	std::cout << std::setw(8) << "Left" << std::setw(8) << "State" << std::setw(14) << "Time" << std::endl;
	std::cout << std::string(66, '-') << std::endl;
	for (int i = 0; i < _book_shelf.size(); ++i) {
		std::cout << std::setw(8) << _book_shelf[i]._no;
		std::cout << std::setw(16) << _book_shelf[i]._name;
		std::cout << std::setw(12) << _book_shelf[i]._author;
		std::cout << std::setw(8) << _book_shelf[i]._num;
		std::cout << std::setw(8) << _book_shelf[i]._status;
		std::cout << std::setw(14) << _book_shelf[i]._time << std::endl;
	}
	std::cout << std::string(66, '-') << std::endl;
}


void BookManager::init_data() {
	std::ifstream ifs1("books.txt");
	int no; std::string name; std::string author; int num; bool stat; std::string t;
	while (ifs1 >> no >> name >> author >> num >> stat >> t) {
		book_info bi(no, name, author, num, stat, t);
		_book_shelf.push_back(bi);
		_type_num++;
	}
	ifs1.close();

	std::ifstream ifs2("users.txt");
	std::string user, usn, psd;
	while (ifs2 >> user >> usn >> psd) {
		usn_psd up(user, usn, psd);
		_usn_psd.push_back(up);
		_user_num++;
	}
	ifs2.close();

	std::ifstream ifs3("borrows.txt");
	std::string bkn, date;
	while (ifs3 >> usn >> bkn >> num >> date) {
		borrow_info bi(bkn, num, date);
		_user_borrow.push_back({ usn,bi });
	}
	ifs3.close();
}


void BookManager::save_data() {
	std::ofstream ofs1("books.txt");
	for (int i = 0; i < _book_shelf.size(); ++i) {
		ofs1 << _book_shelf[i]._no << " " << _book_shelf[i]._name << " " 
			<< _book_shelf[i]._author << " " << _book_shelf[i]._num << " " 
			<< _book_shelf[i]._status << " " << _book_shelf[i]._time << "\n";
	}
	ofs1.close();

	std::ofstream ofs2("users.txt");
	for (int i = 0; i < _usn_psd.size(); ++i) {
		ofs2 << _usn_psd[i]._user << " " << _usn_psd[i]._usn << " " << _usn_psd[i]._psd << "\n";
	}
	ofs2.close();

	std::ofstream ofs3("borrows.txt");
	for (auto i : _user_borrow) {
		ofs3 << i.first << " " << i.second._book_name << " "
			<< i.second._num << " " << i.second._date << "\n";
	}
	ofs3.close();
}

void BookManager::del_books() {
	std::cout << "-->> Del which book: ";
	std::cin >> _choice;
	if (_choice == "q" || _choice == "Q") return;
	for (int i = 0; i < _book_shelf.size(); ++i) {
		if (_book_shelf[i]._name == _choice) {
			_book_shelf.erase(_book_shelf.begin() + i);
			logger.info("Success delete!");
			return;
		}
	}
	logger.warn("No such book can be found");
	this->save_data();
}


void BookManager::mod_info() {
	std::cout << "-->> Modify which book: ";
	std::cin >> _choice;
	if (_choice == "q" || _choice == "Q") return;
	int i;
	for (i = 0; i < _book_shelf.size(); ++i) {
		if (_book_shelf[i]._name == _choice) break;
	}
	if (i == _book_shelf.size()) {
		logger.warn("No such book can be found");
		return;
	}
	// p or P to pass, only title and author
	int no; std::string name; std::string author; int num; bool stat;
	std::cout << "-->> New book id: ";       std::cin >> no;
	std::cout << "-->> New book name: ";     std::cin >> name;
	std::cout << "-->> New author name: ";   std::cin >> author;
	std::cout << "-->> New number: ";        std::cin >> num;
	std::cout << "-->> New status: ";        std::cin >> stat;

	if (name == "p" || name == "P") name = _book_shelf[i]._name;
	if (author == "p" || author == "P") author = _book_shelf[i]._author;
	_book_shelf.erase(_book_shelf.begin() + i);
	book_info bi(no, name, author, num, stat, logger.get_tiem());
	_book_shelf.push_back(bi);
	this->save_data();
}

void BookManager::borrow_books(std::string usn) {
	std::string name;
	std::cout << "-->> Borrow which book: ";
	std::cin >> _choice;
	if (_choice == "q" || _choice == "Q") return;
	int i;
	for (i = 0; i < _book_shelf.size(); ++i) {
		if (_book_shelf[i]._name == _choice) break;
	}
	if (i == _book_shelf.size()) {
		logger.warn("No such book can be found");
		return;
	}
	name = _choice;
	logger.info("There is " + std::to_string(_book_shelf[i]._num) + " left");
	std::cout << "-->> How many you want: ";
	std::cin >> _choice;
	if ((std::stoi(_choice) > _book_shelf[i]._num)) {
		logger.error("Insufficient stock");
		return;
	}
	else {
		_book_shelf[i]._num -= std::stoi(_choice);
		load.info("Process");
	}

	borrow_info bi(name, std::stoi(_choice), logger.get_tiem());
	_user_borrow.push_back({ usn,bi });
	this->save_data();
}


void BookManager::return_books(std::string usn) {
	std::string name;
	std::cout << "-->> Return which book: ";
	std::cin >> _choice;
	if (_choice == "q" || _choice == "Q") return;
	int i;
	for (i = 0; i < _user_borrow.size(); ++i) {
		if (_user_borrow[i].first==usn && _user_borrow[i].second._book_name==_choice) break;
	}
	if (i == _user_borrow.size()) {
		logger.warn("No such book can be found");
		return;
	}

	name = _choice;
	int bNum = _user_borrow[i].second._num;

	logger.info("You have borrowed " + std::to_string(bNum) + " " + name);
	std::cout << "-->> How many you want to return: ";
	std::cin >> _choice;
	if ((std::stoi(_choice) > bNum)) {
		logger.error("Upper limit exceeded");
		return;
	}
	else {
		if ((std::stoi(_choice) == bNum)) {
			_user_borrow.erase(_user_borrow.begin() + i);
			_user_borrow.pop_back();
		}
		else _user_borrow[i].second._num = std::stoi(_choice);
		for (int i = 0; i < _book_shelf.size(); ++i) {
			if (_book_shelf[i]._name == name) {
				_book_shelf[i]._num += std::stoi(_choice);
				break;
			}
		}
		load.info("Process");
	}
	this->save_data();
}


void BookManager::lend_info(std::string usn){
	std::cout << std::string(38, '-') << std::endl;
	std::cout << std::setw(14) << "Title" << std::setw(10) << "Number" << std::setw(14) << "Date\n";
	std::cout << std::string(38, '-') << std::endl;
	for (auto i : _user_borrow) {
		if (i.first==usn) {
			std::cout << std::setw(14) << i.second._book_name << std::setw(10) << i.second._num
				<< std::setw(14) << i.second._date << std::endl;
		}
	}
	std::cout << std::string(38, '-') << std::endl;
}


void BookManager::exit() {
	load.info("Exiting");
	this->save_data();
	logger.info("The system exited and the data saved");
}