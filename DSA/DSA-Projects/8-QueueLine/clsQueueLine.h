#pragma once

#include<queue> //We Using Stl Because of Complex DataType
#include<stack>
#include"clsDate.h"

class clsQueueLine
{
private:

	class clsTicket {

	private:
		short  _Number;
		string _Prefix;
		string _TicketTime;
		short  _WaitingClients;
		short  _AverageServeTime;

	public:
		clsTicket(short Number, string Prefix, short WatingClients, short AverageServeTime):
			_Number(Number),_Prefix(Prefix),_WaitingClients(WatingClients),
			_AverageServeTime(AverageServeTime)
		{
			_TicketTime = clsDate::GetSystemDateTimeString();
		}

		short Number()
		{
			return _Number;
		}

		string Prefix()
		{
			return _Prefix;
		}

		string FullNumber()
		{
			return _Prefix + to_string(_Number);
		}

		short WaitingClients()
		{
			return _WaitingClients;
		}

		string TicketTime()
		{
			return _TicketTime;
		}

		short ExpectedServeTime()
		{
			return _WaitingClients * _AverageServeTime;
		}

		void Print()
		{
			cout << "\n\t\t\t  _______________________\n";
			cout << "\n\t\t\t\t    " << FullNumber();
			cout << "\n\n\t\t\t    " << _TicketTime;
			cout << "\n\t\t\t    Wating Clients = " << _WaitingClients;
			cout << "\n\t\t\t      Serve Time In";
			cout << "\n\t\t\t       " << ExpectedServeTime() << " Minutes.";
			cout << "\n\t\t\t  _______________________\n";

		}
	};

	

	string _Prefix;
	short _TotalTickets;
	short _AverageServeTime;


public:
	queue<clsTicket>QueueLine;

	clsQueueLine(string LinePrefix="A0", short AverageServeTime =0)
	{
		_Prefix = LinePrefix;
		_AverageServeTime = AverageServeTime;
		_TotalTickets = 0;
	}

	short WaitingClients()
	{
		QueueLine.size();
	}

	void IssueTicket()
	{
		_TotalTickets++;
		clsTicket Ticket(_TotalTickets, _Prefix, WaitingClients(), _AverageServeTime);
		QueueLine.push(Ticket);
	}
	 
	string WoIsNext()
	{
		if (QueueLine.empty())
			return "No Clients Left.";

		return QueueLine.front().FullNumber();
	}

	bool ServeNextClient()
	{
		if (QueueLine.empty())
			return false;

		QueueLine.pop();
		return true;
	}
	
	short ServedClients()
	{
		return _TotalTickets - WaitingClients();
	}

	void PrintInfo()
	{
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t\tQueue Info";
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t    Prefix   = " << _Prefix;
		cout << "\n\t\t\t    Total Tickets   = " << _TotalTickets;
		cout << "\n\t\t\t    Served Clients  = " << ServedClients();
		cout << "\n\t\t\t    Wating Clients  = " << WaitingClients(); ;
		cout << "\n\t\t\t _________________________\n";
		cout << "\n";
	}

	void PrintTicketsLineRTL()
	{

		if (QueueLine.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		//we copy the queue in order not to lose the original
		queue <clsTicket> TempQueueLine = QueueLine;


		while (!TempQueueLine.empty())
		{
			clsTicket Ticket = TempQueueLine.front();

			cout << " " << Ticket.FullNumber() << " <-- ";

			TempQueueLine.pop();
		}

		cout << "\n";

	}

	void PrintTicketsLineLTR()
	{
		if (QueueLine.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
			cout << "\n\t\tTickets: ";

		//we copy the queue in order not to lose the original
		queue <clsTicket> TempQueueLine = QueueLine;
		stack <clsTicket> TempStackLine;

		while (!TempQueueLine.empty())
		{
			TempStackLine.push(TempQueueLine.front());
			TempQueueLine.pop();
		}

		while (!TempStackLine.empty())
		{
			clsTicket Ticket = TempStackLine.top();

			cout << " " << Ticket.FullNumber() << " --> ";

			TempStackLine.pop();
		}
		cout << "\n";
	}

	void PrintAllTickets()
	{

		cout << "\n\n\t\t\t       ---Tickets---";

		if (QueueLine.empty())
			cout << "\n\n\t\t\t     ---No Tickets---\n";

		//we copy the queue in order not to lose the original
		queue <clsTicket> TempQueueLine = QueueLine;


		while (!TempQueueLine.empty())
		{
			TempQueueLine.front().Print();
			TempQueueLine.pop();
		}

	}

};


