#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string GetKeyValue(map<string, vector<string>> Map, vector<string> val)
{
	string key;

	for (auto& it : Map)
	{
		for (int i = 0; i < it.second.size(); i++)
		{
			if (it.second[i] == val[0])
			{
				key = it.first;
				break;
			}
		}
	}
	return key;
}

bool findValueExists(map<string, vector<string>>& Map, vector<string> val)
{
	bool a = false;

	for (auto& it : Map)
	{
		for (int i = 0; i < it.second.size(); i++)
		{
			if (it.second[i] == val[0])
			{
				a = true;
				break;
			}
		}
	}

	return a;
}

void PrintKeyAndValues(map<string, vector<string>>& map)
{
	for (auto& it : map)
	{
		cout << it.first << ": ";

		for (int i = 0; i < it.second.size(); i++)
		{
			cout << it.second[i] << " ";
		}

		cout << endl;
	}
}

string ExportToOutText(map<string, vector<string>>& map, string &out)
{
	for (auto& it : map)
	{
		out += it.first + ": ";

		for (int i = 0; i < it.second.size(); i++)
		{
			out += it.second[i] + " ";
		}

		out += "\n";
	}

	return out;
}

int main()
{
	// Map

	map <string, vector<string>> portToFrame;
	map <string, vector<string>> portToAddresses;


	// Vector
	vector<string> vect1;
	vector<string> vect2;
	vector<string> vect3;
	vector<string> vect4;
	vector<string> vect5;
	vector<string> vect6;
	vector<string> vect7;
	vector<string> vect8;

	vector<string> vectAddr1;
	vector<string> vectAddr2;
	vector<string> vectAddr3;
	vector<string> vectAddr4;
	vector<string> vectAddr5;
	vector<string> vectAddr6;
	vector<string> vectAddr7;
	vector<string> vectAddr8;

	//Pairing

	portToFrame.insert(pair <string, vector<string>>("P1", vect1));
	portToFrame.insert(pair <string, vector<string>>("P2", vect2));
	portToFrame.insert(pair <string, vector<string>>("P3", vect3));
	portToFrame.insert(pair <string, vector<string>>("P4", vect4));
	portToFrame.insert(pair <string, vector<string>>("P5", vect5));
	portToFrame.insert(pair <string, vector<string>>("P6", vect6));
	portToFrame.insert(pair <string, vector<string>>("P7", vect7));
	portToFrame.insert(pair <string, vector<string>>("P8", vect8));

	portToAddresses.insert(pair <string, vector<string>>("P1", vectAddr1));
	portToAddresses.insert(pair <string, vector<string>>("P2", vectAddr2));
	portToAddresses.insert(pair <string, vector<string>>("P3", vectAddr3));
	portToAddresses.insert(pair <string, vector<string>>("P4", vectAddr4));
	portToAddresses.insert(pair <string, vector<string>>("P5", vectAddr5));
	portToAddresses.insert(pair <string, vector<string>>("P6", vectAddr6));
	portToAddresses.insert(pair <string, vector<string>>("P7", vectAddr7));
	portToAddresses.insert(pair <string, vector<string>>("P8", vectAddr8));

	//  Read from in.txt and saves data into string
	string outputstring;
	string buffer;
	std::ifstream inputText("in.txt");
	int CountLines = 0;

	while (getline(inputText, buffer))
	{
		outputstring += (buffer + "\n");
		CountLines++;
	}

	string delimiter = "\n";
	int count = 0;

	// Parse all of the string's lines
	for (int i = 0; i < CountLines; i++)
	{
		// Parse string's first line for frame
		string frame = outputstring.substr(outputstring.find("F"), outputstring.find(" "));
		string portNumber = outputstring.substr(outputstring.find("P"), outputstring.find(" "));
		/*string frameInteger = outputstring.substr(outputstring.find("F")+1, outputstring.find(" "));
		string portNumberInteger = outputstring.substr(outputstring.find("P")+1, outputstring.find(" "));*/
		string sourceAddress = outputstring.substr(outputstring.find("-") - 1, 1);
		string destAddress = outputstring.substr(outputstring.find("\n") - 1, 1);

		// Handle whitespace error
		if (i > 8)
		{
			portNumber = outputstring.substr(outputstring.find("P"), outputstring.find(" ") - 1);
		}

		// Switch Logic

		// Add current source address to the port-address map
		auto crsit = portToAddresses.find(portNumber);
		(*crsit).second.push_back(sourceAddress);

		// Look in table to see if destination address is on any port
		vector<string> temp;
		temp.push_back(destAddress);

		// If it is located, send the frame to the destination address
		bool ValueExists = findValueExists(portToAddresses, temp);

		// If destination address is X, then broadcast to all ports
		if (destAddress == "X")
		{
			auto it = portToFrame.find(portNumber);

			// Assign the current source address to current port number


			// Broadcast frame to all ports
			for (auto it4 = portToFrame.begin(); it4 != portToFrame.end(); ++it4)
			{
				//cout << "It4: " << (*it4).first << endl;
				if (it4 == it)
				{
					continue;
				}
				else
				{
					(*it4).second.push_back(frame);
				}
			}
		}
		else if (ValueExists == true)
		{
			string GetKey = GetKeyValue(portToAddresses, temp);

			auto it10 = portToFrame.find(GetKey);
			(*it10).second.push_back(frame);
		}
		// If not, broadcast frame to all ports except from the current port
		else
		{
			auto currentPort = portToFrame.find(portNumber);

			for (auto broadcast = portToFrame.begin(); broadcast != portToFrame.end(); ++broadcast)
			{
				if (currentPort == broadcast)
				{
					continue;
				}
				else
				{
					(*broadcast).second.push_back(frame);
				}
			}
		}

		temp.pop_back();

		// Remove string's first line until the end
		outputstring.erase(0, outputstring.find(delimiter) + delimiter.length());
	}

	// Print mapping of port : frames
	PrintKeyAndValues(portToFrame);

	// Save solution to string and export it
	string outString;
	ExportToOutText(portToFrame, outString);

	ofstream out("out.txt");
	out << outString;
	out.close();


	system("pause");
	return 0;
}