//============================================================================
// Name        : Assign1_CS2B.cpp
// Author      : Zade Lobo
// Date        : Fall 2017
// Version     : 1.0.3
// Copyright   : Copyright (C). CS Department Foothill College 2017. All rights reserved.
// Description : Simulation of a movie ticket vendor using pointers, objects, and arrays
// Revisions History:
// 		October 10, 2017 / Program was written
//		October 10, 2017 / Formatting error was fixed to make the output look "cleaner"
//		October 10, 2017 / Runtime errors fixed of infinite loop problem
//    	October 11, 2017 / Formatting, new lines
//============================================================================

#include <iostream>
using namespace std;
const int g_kArraySize = 8;

class Movie
{
public:
	Movie();
	void set_movie_name(string name);
	void set_movie_price(double price);
	void set_movie_seats(int seats);
	string get_movie_name();
	double get_movie_price();
	int get_movie_seats();
	double purchase_tickets(int tickets);
	void display();
	~Movie();
private:
	string movie_name_;
	int movie_seats_;
	double movie_price_;
};

Movie::Movie()
{
	movie_seats_ = 0;
	movie_price_ = 0.0;
}

void Movie::set_movie_name(string name)
{
	movie_name_ = name;
}

void Movie::set_movie_price(double price)
{
	movie_price_ = price;
}

void Movie::set_movie_seats(int seats)
{
	movie_seats_ = seats;
}

string Movie::get_movie_name()
{
	return movie_name_;
}

double Movie::get_movie_price()
{
	return movie_price_;
}

int Movie::get_movie_seats()
{
	return movie_seats_;
}

double Movie::purchase_tickets(int tickets)
{
	if (get_movie_seats() < tickets)
	{
		return -1;
	}
	else
	{
		set_movie_seats(get_movie_seats()-tickets);
		return get_movie_price()*tickets;
	}
}

void Movie::display()
{
	cout << "Name: " << get_movie_name() << endl;
	cout << "Seats Remaining: " << get_movie_seats() << endl;
	cout << "Price: $" << get_movie_price() << endl;
	cout << "************************" << endl;
}

Movie::~Movie()
{

}

class MovieTicketMaster
{
public:
	MovieTicketMaster();
	MovieTicketMaster(string theater_name, string theater_location);
	void init();
	void run();
	void menu();
	void view_movies();
	void search_movie();
	Movie* find_movie(string name);
	void purchase_ticket();
	~MovieTicketMaster();
private:
	string theater_name_;
	string theater_location_;
	Movie movies_ [g_kArraySize];
	int input_;
};

MovieTicketMaster::MovieTicketMaster()
{
	input_ = 0;
}

MovieTicketMaster::MovieTicketMaster(string theater_name, string theater_location)
{
	theater_name_ = theater_name;
	theater_location_ = theater_location;
	input_ = 0;
}

void MovieTicketMaster::init()
{
	string movie_names [g_kArraySize]  =  {"Blade Runner", "American Made", "Wonder Woman", "The Stray", "Home Again", "Cars 3", "Baby Driver", "Wind River"};
	double movie_prices [g_kArraySize] = {12.50, 13.00, 11.25, 9.50, 6.75, 9.50, 10.50, 8.75};
	int movie_seats [g_kArraySize] = {53, 72, 108, 185, 176, 193, 142, 134};
	Movie movie1;
	Movie movie2;
	Movie movie3;
	Movie movie4;
	Movie movie5;
	Movie movie6;
	Movie movie7;
	Movie movie8;
	Movie* p_movie = NULL;
	p_movie = movies_;
	string* p_names = NULL;
	p_names = movie_names;
	int* p_seats = NULL;
	p_seats = movie_seats;
	double* p_prices = NULL;
	p_prices = movie_prices;
	for (int i=0; i<g_kArraySize; ++i)
	{
		p_movie->set_movie_name(*p_names);
		p_movie->set_movie_seats(*p_seats);
		p_movie->set_movie_price(*p_prices);
		p_movie++;
		p_names++;
		p_seats++;
		p_prices++;
	}
}

void MovieTicketMaster::view_movies()
{
	cout << "Here are the movies on display at this theater: "  << endl;
	Movie* p_movie = NULL;
	p_movie = movies_;
	for (int i=0; i<g_kArraySize; ++i)
	{
		p_movie->display();
		p_movie++;
	}
}

Movie* MovieTicketMaster::find_movie(string name)
{
	Movie* p_movie = NULL;
	p_movie = movies_;
	for (int i=0; i<g_kArraySize; ++i)
	{
		if (p_movie->get_movie_name() == name)
		{
			return p_movie;
		}
		p_movie++;
	}
	return NULL;
}

void MovieTicketMaster::search_movie()
{
	cout << "Please enter the name of the movie you would like to search for: " << endl;
	string keyword;
	string part1;
	string part2;
	cin >> part1;
	cin >> part2;
	keyword = part1 + ' ' + part2;
	if (find_movie(keyword)==NULL)
	{
		cout << "No movie matched your search. " << endl;
	}
	else
	{
		find_movie(keyword)->display();
	}
}

void MovieTicketMaster::purchase_ticket()
{
	string keyword;
	int requested_tickets;
	double total_price;
	cout << "What movie would you like to purchase tickets for?" << endl;
	string part1;
	string part2;
	cin >> part1;
	cin >> part2;
	keyword = part1 + ' ' + part2;
	cout << "How many tickets would you like to purchase?" << endl;
	cin >> requested_tickets;
	if (find_movie(keyword)==NULL)
	{
		cout << "No movie matched your search. " << endl;
	}
	else
	{
		find_movie(keyword)->display();
		total_price = find_movie(keyword)->purchase_tickets(requested_tickets);
		if (total_price==-1)
		{
			cout << "The show has been sold out or there are not enough tickets available per your request." << endl;
		}
		else
		{
			cout << "The tickets have been ordered. " << endl;
			cout << "The total that you must pay is $" << total_price << ". " << endl;
		}
	}
}

void MovieTicketMaster::run()
{
	do
	{
		menu();
		switch (input_)
		{
			case 1: view_movies();
			break;
			case 2: search_movie();
			break;
			case 3: purchase_ticket();
			break;
		}
	} while (input_ != 4);
}

void MovieTicketMaster::menu()
{
	cout << "MOVIE TICKET MASTER" << endl;
	cout << "Theater: " << theater_name_ << " at " << theater_location_ << endl;
	cout << "Movies that Move You!" << endl;
	cout << endl;
	cout << "1. View All Movies" << endl;
	cout << "2. Search a Movie" << endl;
	cout << "3. Purchase a Ticket" << endl;
	cout << "4. Quit" << endl;
	cin >> input_;
}

MovieTicketMaster::~MovieTicketMaster()
{
	cout<<"Theater " << theater_name_ << " at " << theater_location_ << " has been closed." << endl;
}

int main() {
	MovieTicketMaster* p_vendor = NULL;
	p_vendor = new MovieTicketMaster("AMC 16", "Vallco Mall");
	p_vendor->init();
	p_vendor->run();
	delete p_vendor;
	exit(0);
}
