#include "structures.h"

int buffLen(const int* buff) {
	int i = 0;
	for (; buff[i] != 300; ++i) {}
	return i;
}

obitfstream& print(obitfstream& out, link& a, int* buff) {
	while (a.length > 255) {
		int lenght = buffLen(buff);
		out << (char)a.offset;
		out << (char)255;
		if (lenght != 0) {
			out << (char)buff[255 % lenght];//migth be problem
		}
		a.length -= 256;
		if (lenght != 0) {
			a.offset = 256 % lenght;
		}
	}
	out << (char)a.offset;
	out << (char)a.length;
	out << (char)a.next;
	return out;
}

obitfstream& operator<< (obitfstream& out, link& a) {
	while (a.length > 255) {
		out << (char)a.offset;
		out << (char)255;
		out << (char)1;
		a.length -= 256;
	}
	out << (char)a.offset;
	out << (char)a.length;
	out << (char)a.next;
	//std::cout << (int)a.offset;
	//std::cout << (int)a.length;
	//std::cout << (char)a.next;
	//std::cout << std::endl;
	return out;
}

ibitfstream& operator>> (ibitfstream& in, link& a) {
	if ((a.offset = in.get()) == EOF) { a.offset = 300; }
	a.length = in.get();
	int ch = 0;
	if ((a.next = in.get()) == 255) {
		if (in.peek() == EOF) {
			a.next = 300;
		}
	}
	//a.next = in.get();
	return in;
}

void standartPush(int* mass, char ch) {
	if (mass[3] != 300) {
		for (int i = 0; i < 3; ++i) {
			mass[i] = mass[i + 1];
		}
		mass[3] = (int)(unsigned char)(ch);
	}
	else {
		int i = 0;
		while (mass[i] != 300) { ++i; }
		mass[i] = (int)(unsigned char)ch;
	}
}

void makeLink(link& ellement, char ch, ibitfstream& inFile, cash& cashBuff, obitfstream& outFile) {
	int counter = 0;
	for (int i = 0; i < 128; ++i) {
		if (cashBuff[i] == ch && cashBuff[i] != 300) {
			int startIndx = i;
			//int length = cashBuff.getLength();
			while (cashBuff[i] == ch && counter < 255) {
				cashBuff.push(ch);
				ch = (char)inFile.get();
				++i;
				++counter;
			}
			if (counter > 254) {
				ellement.offset = startIndx;
				ellement.length = 255;
				ellement.next = (int)(unsigned char)ch;
				cashBuff.push(ch);
				cashBuff.reSet();
				//outFile << ellement;
			}
			else {
				ellement.offset = startIndx;
				ellement.length = counter;
				ellement.next = (int)(unsigned char)ch;
				cashBuff.push(ch);
				cashBuff.reSet();
			}
			break;
		}
		if (i + 1 == 128 && ellement.length == 0 || cashBuff.getISymbol(i) == 300) {
			cashBuff.push(ch);
			ellement.offset = 0;
			ellement.length = 0;
			ellement.next = (int)(unsigned char)ch;
			cashBuff.reSet();
			break;
		}
	}
}

void writeLink(link& ellement, cash& cashBuff, obitfstream& outFile) {
	if (ellement.length == 0) {
		cashBuff.push(ellement.next);
		outFile << (char)ellement.next;
		//std::cout << (char)ellement.next;
	}
	else {
		int balance = ellement.offset;
		for (int i = 0; i < ellement.length; ++i) {
			if (balance + i >= cashBuff.end_of_buff || cashBuff[balance + i] == 300) {
				balance = cashBuff.start_of_buff - i;
			}
			//std::cout << (char)cashBuff[balance + i];
			outFile << (char)cashBuff[balance + i];
			cashBuff.push(cashBuff[balance + i]);
		}
		cashBuff.push(ellement.next);
		if (ellement.next != 300) {
			outFile << (char)ellement.next;
			//std::cout << (char)ellement.next;
		}
	}
	cashBuff.setBuffer();
	cashBuff.reSet();
}

void RLEcomBACK(ibitfstream& inFile, obitfstream& outFile) {
	int ch = 0;
	cash cashBuff;
	while ((ch = inFile.get()) != EOF) {
		link ellement;
		makeLink(ellement, (char)ch, inFile, cashBuff, outFile);
		outFile << ellement;
	}
}

void deRLEcomBACK(ibitfstream& inFile, obitfstream& outFile) {
	int ch = 0;
	link ellement;
	cash cashBuff;
	while (inFile >> ellement) {
		writeLink(ellement, cashBuff, outFile);
	}
}