#ifndef BOOK_MANAGER
#define BOOK_MANAGER

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>

#include "load.h"
#include "logger.h"


namespace bookmanager {

class BookManager {
public:
	struct book_info {
		int _no;   // 4 number
		std::string _name;
		std::string _author;
		int _num;
		bool _status;  // can this book be borrowed?
		std::string _time;
		book_info(int no, std::string name, std::string author, int num, bool stat, std::string t) :
			_no(no), _name(name), _author(author), _num(num), _status(stat), _time(t) {};
	}; // book information

	struct borrow_info {
		std::string _book_name;
		int _num;
		std::string _date;

		borrow_info() {};
		borrow_info(std::string name, int num, std::string date) :
			_book_name(name), _num(num), _date(date) {};
	}; // borrow information

	struct usn_psd {
		std::string _user;
		std::string _usn;
		std::string _psd;
		usn_psd(std::string user, std::string usn, std::string psd) :_user(user), _usn(usn), _psd(psd) {};
	}; // username and password

	BookManager(int num1, int num2) :_type_num(num1), _user_num(num2) {};

	void screen(std::string& user, std::string& usn);
	bool login(std::string user, std::string usn, std::string pas);
	void enroll(std::string user, std::string usn, std::string pas);

	void add_books();
	void show_books();
	void borrow_books(std::string usn);
	void return_books(std::string usn);
	void lend_info(std::string usn);
	void init_data();
	void save_data();
	void del_books();
	void mod_info();
	void exit();

private:
	int _type_num;
	int _user_num;

	std::string _choice;

	std::vector<book_info> _book_shelf;
	std::vector<std::pair<std::string, borrow_info>> _user_borrow;
	std::vector<usn_psd> _usn_psd;
};



} // namespace


#endif // !BOOK_MANAGER

