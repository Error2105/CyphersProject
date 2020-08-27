#pragma once
#include <string>
class Enigma
{
private:
	//std::string rotor1 = "JGDQOXUSCAMIFRVTPNEWKBLZYH";
	//std::string rotor2 = "NTZPSFBOKMWRCJDIVLAEYUXHGQ";
	//std::string rotor3 = "JVIUBHTCDYAKEQZPOSGXNRMWFL";
	//std::string rotor4 = "QYHOGNECVPUZTFDJAXWMKISRBL";
	//std::string rotor5 = "QWERTZUIOASDFGHJKPYXCVBNML";

	int wiring1[26][2] = { {0, 9}, {1, 6}, {2, 3}, {3, 16}, {4, 14}, {5, 23}, {6, 20}, {7, 18}, {8, 2}, {9, 0}, {10, 12}, {11, 8}, {12, 5}, {13, 17}, {14, 21}, {15, 19}, {16, 15}, {17, 13}, {18, 4}, {19, 22}, {20, 10}, {21, 1}, {22, 11}, {23, 25}, {24, 24}, {25, 7} };
	int wiring2[26][2] = { {0, 13}, {1, 19}, {2, 25}, {3, 15}, {4, 18}, {5, 5}, {6, 1}, {7, 14}, {8, 10}, {9, 12}, {10, 22}, {11, 17}, {12, 2}, {13, 9}, {14, 3}, {15, 8}, {16, 21}, {17, 11}, {18, 0}, {19, 4}, {20, 24}, {21, 20}, {22, 23}, {23, 7}, {24, 6}, {25, 16} };
	int wiring3[26][2] = { {0, 9}, {1, 21}, {2, 8}, {3, 20}, {4, 1}, {5, 7}, {6, 19}, {7, 2}, {8, 3}, {9, 24}, {10, 0}, {11, 10}, {12, 4}, {13, 16}, {14, 25}, {15, 15}, {16, 14}, {17, 18}, {18, 6}, {19, 23}, {20, 13}, {21, 17}, {22, 12}, {23, 22}, {24, 5}, {25, 11} };
	int wiring4[26][2] = { {0, 16}, {1, 24}, {2, 7}, {3, 14}, {4, 6}, {5, 13}, {6, 4}, {7, 2}, {8, 21}, {9, 15}, {10, 20}, {11, 25}, {12, 19}, {13, 5}, {14, 3}, {15, 9}, {16, 0}, {17, 23}, {18, 22}, {19, 12}, {20, 10}, {21, 8}, {22, 18}, {23, 17}, {24, 1}, {25, 11} };
	int wiring5[26][2] = { {0, 16}, {1, 22}, {2, 4}, {3, 17}, {4, 19}, {5, 25}, {6, 20}, {7, 8}, {8, 14}, {9, 0}, {10, 18}, {11, 3}, {12, 5}, {13, 6}, {14, 7}, {15, 9}, {16, 10}, {17, 15}, {18, 24}, {19, 23}, {20, 2}, {21, 21}, {22, 1}, {23, 13}, {24, 12}, {25, 11} };
	int endThing[26][2] = { {0, 21}, {1, 10}, {2, 22}, {3, 17}, {4, 6}, {5, 8}, {6, 4}, {7, 19}, {8, 5}, {9, 25}, {10, 1}, {11, 20}, {12, 18}, {13, 15}, {14, 16}, {15, 13}, {16, 14}, {17, 3}, {18, 12}, {19, 7}, {20, 11}, {21, 0}, {22, 2}, {23, 24}, {24, 23}, {25, 9} };

	int plugboard[26] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int rotorConfiguration[3][2] = { {1, 0}, {2, 0}, {3, 0}};

public:
	Enigma();
	~Enigma();
	int getPlugValue(int input_key);
	void setPlugValue(int character_one, int character_two);
	int getWiringOutput(int rotor_type, int input, bool forward, int position);
	int calculateOutput(int input);
	void setRotors(int rotor, int configuration, int position);
	void setRotors(int rotor, int position);
	int getRotorConnection(int position);
	int getRotorNum(int position);
	void resetPlugs();

}; 