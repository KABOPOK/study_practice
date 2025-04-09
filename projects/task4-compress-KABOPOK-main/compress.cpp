#include "structures.h"
bool help() {
	std::cout << "Input: programm.exe " << std::endl
		<< "Use keys for encode file.txt: -huffman -mtf -lz77" << std::endl
		<< "Input: file.txt" << std::endl
		<< "Input: outFile.txt";
	return true;
}

int main(int argc, const char* argv[])
{
	bool MTF = false;
	bool lz77 = false;
	bool HUF = false;
	bool decode = false;
	bool turn_down = false;

	if (argc < 4 || argc>6) { turn_down = help(); }

	if (turn_down) { return 0; }

	for (int i = 1; i < argc; ++i) {
		if (0 == strcmp(argv[i], "-d")) {
			decode = true;
			continue;
		}
		if (0 == strcmp(argv[i], "-mtf")) {
			MTF = true;
			continue;
		}
		if (0 == strcmp(argv[i], "-lz77")) {
			lz77 = true;
			continue;
		}
		if (0 == strcmp(argv[i], "-huffman")) {
			HUF = true;
			continue;
		}
		if (0 == strcmp(argv[i], "?")) {
			turn_down = help();
			continue;
		}
		if (0 == strcmp(argv[i], "-h")) {
			turn_down = help();
			continue;
		}
	}

	if (turn_down) { return 0; }

	if (decode) {
		ibitfstream inFile(argv[2]);
		obitfstream outFile(argv[3]);
		int ch = 0;
		ch = inFile.get();
		switch (ch) {
		case 1:
			deMTC(inFile, outFile);
			break;
		case 2:
			deRLEcomBACK(inFile, outFile);
			break;
		case 4:
			deHUFman(inFile, outFile);
			break;
		default:
			break;
		}
		if (ch == 3) {
			obitfstream mycop_o("mycop.txt");

			deRLEcomBACK(inFile, mycop_o);

			mycop_o.close();
			inFile.close();

			ibitfstream mycop_i("mycop.txt");

			deMTC(mycop_i, outFile);

			mycop_i.close();
		}
		else if (ch == 5) {
			obitfstream mycop_o("mycop.txt");

			deHUFman(inFile, mycop_o);

			mycop_o.close();
			inFile.close();

			ibitfstream mycop_i("mycop.txt");

			deMTC(mycop_i, outFile);

			mycop_i.close();
		}
		else if (ch == 6) {
			obitfstream mycop_o("mycop.txt");

			deHUFman(inFile, mycop_o);

			mycop_o.close();
			inFile.close();

			ibitfstream mycop_i("mycop.txt");

			deRLEcomBACK(mycop_i, outFile);

			mycop_i.close();
		}
		else if (ch == 7) {
			deHUFman(inFile, outFile);

			inFile.close();
			outFile.close();

			ibitfstream outFile_i(argv[3]);
			obitfstream mycop_o("mycop.txt");

			deRLEcomBACK(outFile_i, mycop_o);

			outFile_i.close();
			mycop_o.close();

			ibitfstream mycop_i("mycop.txt");
			obitfstream outFile_2(argv[3]);

			deMTC(mycop_i, outFile_2);

			mycop_i.close();
			outFile_2.close();
		}
		inFile.close(); //// double closing of file
		outFile.close();
	}

	if (MTF && !lz77 && !HUF) {
		ibitfstream inFile(argv[2]);
		obitfstream outFile(argv[3]);

		if (!inFile) { std::cout << "can't open input file"; }
		if (!outFile) { std::cout << "can't open output file"; }

		//MTF
		outFile.put(1);
		newMTC(inFile, outFile);
		//END
		inFile.close();
		outFile.close();

	}

	else if (!MTF && lz77 && !HUF) {
		ibitfstream inFile(argv[2]);
		obitfstream outFile(argv[3]);

		if (!inFile) { std::cout << "can't open input file"; }
		if (!outFile) { std::cout << "can't open output file"; }

		outFile.put(2);
		RLEcomBACK(inFile, outFile);

		inFile.close();
		outFile.close();
	}

	else if (!MTF && !lz77 && HUF) {
		ibitfstream inFile(argv[2]);
		obitfstream outFile(argv[3]);

		if (!inFile) { std::cout << "can't open input file"; }
		if (!outFile) { std::cout << "can't open output file"; }

		outFile.put(4);
		HUFman(inFile, outFile);

		inFile.close();
		outFile.close();
	}

	else if (!MTF && lz77 && HUF) {
		ibitfstream inFile(argv[3]);
		obitfstream mycop_i("mycop.txt");

		if (!inFile) { std::cout << "can't open input file"; }

		RLEcomBACK(inFile, mycop_i);

		inFile.close();
		mycop_i.close();

		ibitfstream mycop_o("mycop.txt");
		obitfstream outFile(argv[4]);

		if (!outFile) { std::cout << "can't open output file"; }

		outFile.put(6);
		HUFman(mycop_o, outFile);

		mycop_o.close();
		outFile.close();
	}

	else if (MTF && !lz77 && HUF) {
		ibitfstream inFile(argv[3]);
		obitfstream mycop_i("mycop.txt");

		if (!inFile) { std::cout << "can't open input file"; }

		newMTC(inFile, mycop_i);

		inFile.close();
		mycop_i.close();

		ibitfstream mycop_o("mycop.txt");
		obitfstream outFile(argv[4]);

		if (!outFile) { std::cout << "can't open output file"; }

		outFile.put(5);
		HUFman(mycop_o, outFile);

		mycop_o.close();
		outFile.close();
	}

	else if (MTF && lz77 && !HUF) {
		ibitfstream inFile(argv[3]);
		obitfstream mycop_i("mycop.txt");

		if (!inFile) { std::cout << "can't open input file"; }

		newMTC(inFile, mycop_i);

		inFile.close();
		mycop_i.close();

		ibitfstream mycop_o("mycop.txt");
		obitfstream outFile(argv[4]);

		if (!outFile) { std::cout << "can't open output file"; }

		outFile.put(3);
		RLEcomBACK(mycop_o, outFile);

		mycop_o.close();
		outFile.close();
	}

	else if (MTF && lz77 && HUF) {
		ibitfstream inFile(argv[4]);
		obitfstream outFile(argv[5]);

		if (!inFile) { std::cout << "can't open input file"; }
		if (!outFile) { std::cout << "can't open output file"; }

		MTC(inFile, outFile);

		inFile.close();
		outFile.close();

		ibitfstream outFile_i(argv[5]);
		obitfstream mycop_o("mycop.txt");

		RLEcomBACK(outFile_i, mycop_o);

		outFile_i.close();
		mycop_o.close();

		ibitfstream mycop_i("mycop.txt");
		obitfstream outFile_2(argv[5]);

		outFile_2.put(7);
		HUFman(mycop_i, outFile_2);

		mycop_i.close();
		outFile_2.close();
	}
}