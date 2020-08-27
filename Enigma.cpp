#include "Enigma.h"
#include <iostream>
Enigma::Enigma() //constructor
{

}

Enigma::~Enigma() //destructor
{

}

int Enigma::getPlugValue(int input_key) //return the linked plug to inputted plug (if not linked, return -1)
{
	return plugboard[input_key];
}

void Enigma::setPlugValue(int character_one, int character_two) //link two plugs together
{
	plugboard[character_one] = character_two;
	plugboard[character_two] = character_one;
}



void Enigma::setRotors(int rotor, int configuration, int position) //set a rotor into a specific position with a specific configuration
{
	rotorConfiguration[position][0] = rotor;
	rotorConfiguration[position][1] = configuration;
}

void Enigma::setRotors(int rotor, int position) //same as previous, but not updating the configuration
{
	rotorConfiguration[position][0] = rotor;
}

int Enigma::getRotorConnection(int position) //return the current configuration of the rotor in the selected position
{
	return rotorConfiguration[position][1];
}

int Enigma::getRotorNum(int position) //get the number of the rotor in the selected position
{
	return rotorConfiguration[position][0];
}



void Enigma::resetPlugs() //reset all the plugs to -1
{
	for (int i = 0; i < 26; i++)
	{
		plugboard[i] = -1;
	}
}

int Enigma::getWiringOutput(int rotor_num, int input, bool forward, int position) //calculate the output of a rotor based on the input
{

	if (forward) //if the signal is passing through the rotor for the first time
	{
		switch (rotor_num) //select the correct rotor wiring, then get the output stored in wiringX[input][1] based on the current rotor and its configuration
		{
		case 1: input = (input + rotorConfiguration[position][1]) % 26;  return wiring1[input][1]; break;
		case 2: input = (input + rotorConfiguration[position][1]) % 26;  return wiring2[input][1]; break;
		case 3: input = (input + rotorConfiguration[position][1]) % 26;  return wiring3[input][1]; break;
		case 4: input = (input + rotorConfiguration[position][1]) % 26;  return wiring4[input][1]; break;
		case 5: input = (input + rotorConfiguration[position][1]) % 26;  return wiring5[input][1]; break;
		case 6: input = (input) % 26; return endThing[input][1]; break;
		}
	}
	else //the signal is passing through the rotor for the second time (going backwards)
	{
		int output = 0;
		switch (rotor_num) //select correct rotor wiring and return the output stored in wiringX[i][0] offset by the current rotor configuration
		{
		case 1:  
			for (int i = 0; i < 26; i++)
			{
				if (input == wiring1[i][1])
				{
					output = (wiring1[i][0] - rotorConfiguration[position][1]);
				
					while (output < 0)
					{
						output = 26 + output;
					}
					output = output % 26;
					return output;
				}
			}
		case 2:  for (int i = 0; i < 26; i++)
		{
			if (input == wiring2[i][1])
			{
				output = (wiring2[i][0] - rotorConfiguration[position][1]);

				while (output < 0)
				{
					output = 26 + output;
				}
				output = output % 26;
				return output;
			}
		}
		case 3:  for (int i = 0; i < 26; i++)
		{
			if (input == wiring3[i][1])
			{
				output = (wiring3[i][0] - rotorConfiguration[position][1]);

				while (output < 0)
				{
					output = 26 + output;
				}
				output = output % 26;
				return output;
			}
		}
		case 4:  for (int i = 0; i < 26; i++)
		{
			if (input == wiring4[i][1])
			{
				output = (wiring4[i][0] - rotorConfiguration[position][1]);

				while (output < 0)
				{
					output = 26 + output;
				}
				output = output % 26;
				return output;
			}
		}
		case 5: for (int i = 0; i < 26; i++)
		{
			if (input == wiring5[i][1])
			{
				output = (wiring5[i][0] - rotorConfiguration[position][1]);

				while (output < 0)
				{
					output = 26 + output;
				}
				output = output % 26;
				return output;
			}
		}
		case 6: input = (input) % 26; return endThing[input][0]; break;
		}
	}

}

int Enigma::calculateOutput(int input) //take the inputted character and send it through each section to return the encrypted character
{
	int plug_mutation = input;
	if (getPlugValue(input) != -1) //check if the inputted character is linked to another character on the plugboard
	{
		plug_mutation = getPlugValue(input); //change the inputted character to the linked character
	}
	int rotor1_output = getWiringOutput(getRotorNum(2) , plug_mutation, true, 2); //pass value through rotor in slot 3
	int rotor2_output = getWiringOutput(getRotorNum(1) , rotor1_output, true, 1); //pass the output of previous section through rotor in slot 2
	int rotor3_output = getWiringOutput(getRotorNum(0) , rotor2_output, true, 0); //pass the output of previous section through rotor in slot 1
	int endThing_output = getWiringOutput(6, rotor3_output, true, -1); //pass the output of previous section through the reflector
	int rotor3_output2 = getWiringOutput(getRotorNum(0), endThing_output, false, 0); //pass the output of previous section through rotor in slot 1, but backwards
	int rotor2_output2 = getWiringOutput(getRotorNum(1) , rotor3_output2, false, 1); //pass the output of previous section through rotor in slot 2, but backwards
	int rotor1_output2 = getWiringOutput(getRotorNum(2), rotor2_output2, false, 2); //pass the output of previous section through rotor in slot 3, but backwards
	if (getPlugValue(rotor1_output2) != -1) //check if the outputted character is linked to another character on the plugboard
	{
		plug_mutation = getPlugValue(rotor1_output2); //change the outputted character to the linked character
		return plug_mutation; //return the linked character
	}
	else 
	{
		return rotor1_output2; //return the encrypted character
	}
	
}