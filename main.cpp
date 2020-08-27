#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include "Enigma.h"

/*
THANK YOU FOR LOOKING AT MY PROJECT.
IT WAS A LOT OF FUN WORKING WITH THESE CYPHERS AS WELL AS LEARNING HOW TO USE SFML
-MATTHEW.L
*/
using namespace std;

//prototypes
void Caeser();
void Vigenere();
void Enigma_cypher();

int main()
{
	while (true) //continue running until user quits
	{
		cout << "Please select which cypher you wish to view:" << endl << "1. Ceaser Cypher" << endl << "2. Vigenere cipher" << endl << "3. Enigma cipher" << endl << "4. Quit" << endl;
		string test = "0";
		cin >> test;
		if (test == "1")
		{
			Caeser();
		}
		else if (test == "2")
		{
			Vigenere();
		}
		else if (test == "3")
		{
			Enigma_cypher();
		}
		else if (test == "4")
		{
			return 0;
		}
		else
		{
			cout << "Error: Invalid Input." << endl;
		}
		
	}
	
	
}

void Caeser() 
{
	
	sf::RenderWindow window(sf::VideoMode(850, 850), "Caeser Shift"); //create window

	sf::Font font; //import text font
	if(!font.loadFromFile("arial.ttf"))
	{
		//error
		cout << "ERROR!" << endl;
	}

	//CREATE AND CONFIGURE ALL SPRITES USED

	sf::Text title_string;
	title_string.setFillColor(sf::Color::White);
	title_string.setFont(font);
	title_string.setCharacterSize(48);
	title_string.setPosition(50, 25);
	title_string.setString("Ceaser Cypher");

	sf::Text subtitle_string1;
	subtitle_string1.setFillColor(sf::Color::White);
	subtitle_string1.setFont(font);
	subtitle_string1.setCharacterSize(18);
	subtitle_string1.setPosition(50, 100);
	subtitle_string1.setString("Encrpytion: Shift every letter up the alphabet equal to the number acting as a key.");

	sf::Text subtitle_string2;
	subtitle_string2.setFillColor(sf::Color::White);
	subtitle_string2.setFont(font);
	subtitle_string2.setCharacterSize(18);
	subtitle_string2.setPosition(50, 125);
	subtitle_string2.setString("Decrpytion: Shift every letter down the alphabet equal to the number acting as a key.");

	sf::Text subtitle_string3;
	subtitle_string3.setFillColor(sf::Color::White);
	subtitle_string3.setFont(font);
	subtitle_string3.setCharacterSize(18);
	subtitle_string3.setPosition(50, 800);
	subtitle_string3.setString("Security: Allows for X potential combinations, equal to the length of the alphabet used minus one.");

	sf::String user_input;
	sf::Text user_text;
	user_text.setFillColor(sf::Color::Black);
	user_text.setFont(font);
	user_text.setCharacterSize(48);
	user_text.setPosition(300, 250);
	vector<char> char_vector;

	sf::Text encrpyted_text;
	encrpyted_text.setFillColor(sf::Color::Black);
	encrpyted_text.setFont(font);
	encrpyted_text.setCharacterSize(48);
	encrpyted_text.setPosition(300, 600);

	sf::Text shift_num;
	int shift_counter = 0;
	shift_num.setFont(font);
	shift_num.setString(to_string(shift_counter));
	shift_num.setCharacterSize(48);
	shift_num.setFillColor(sf::Color::Black);

	sf::Text erase_text;
	erase_text.setFont(font);
	erase_text.setString("Erase");
	erase_text.setCharacterSize(30);
	erase_text.setFillColor(sf::Color::Black);
	erase_text.setPosition(410, 425);

	sf::Text Encrypt_text;
	Encrypt_text.setFont(font);
	Encrypt_text.setString("Encrypt");
	Encrypt_text.setCharacterSize(20);
	Encrypt_text.setFillColor(sf::Color::Black);
	Encrypt_text.setPosition(610, 435);

	sf::RectangleShape back_wall;
	back_wall.setSize(sf::Vector2f(50, 50));
	back_wall.setFillColor(sf::Color::Color(25, 25, 25));

	sf::RectangleShape back_wall2;
	back_wall2.setSize(sf::Vector2f(50, 50));
	back_wall2.setFillColor(sf::Color::Color(50, 50, 50));

	sf::Texture arrows;
	if (!arrows.loadFromFile("arrows.png"))
	{
		//Error
		cout << "ERROR!" << endl;
	}

	sf::Texture textbox;
	if (!textbox.loadFromFile("Textbox.png"))
	{
		//Error
		cout << "Error!" << endl;
	}

	sf::Sprite spr_arrowup;
	spr_arrowup.setTexture(arrows);
	spr_arrowup.setTextureRect(sf::IntRect(0, 0, 64, 64));
	sf::Sprite spr_arrowdown;
	spr_arrowdown.setTexture(arrows);
	spr_arrowdown.setTextureRect(sf::IntRect(0, 64, 64, 64));

	sf::Sprite spr_typebox1;
	spr_typebox1.setTexture(textbox);
	spr_typebox1.setTextureRect(sf::IntRect(0, 0, 40, 64));

	sf::Sprite spr_typebox2;
	spr_typebox2.setTexture(textbox);
	spr_typebox2.setTextureRect(sf::IntRect(10, 0, 40, 64));

	sf::Sprite spr_typebox3;
	spr_typebox3.setTexture(textbox);
	spr_typebox3.setTextureRect(sf::IntRect(10, 0, 64, 64));

	sf::Sprite spr_textbox;
	spr_textbox.setTexture(textbox);
	sf::Sprite spr_erase;
	spr_erase.setTexture(textbox);
	spr_erase.scale(sf::Vector2f(1.5f, 1.5f));
	sf::Sprite spr_encrypt;
	spr_encrypt.setTexture(textbox);
	spr_encrypt.scale(sf::Vector2f(1.5f, 1.5f));

	spr_arrowup.setPosition(50, 300);
	spr_arrowdown.setPosition(50, 450);
	spr_textbox.setPosition(50, 375);
	spr_erase.setPosition(400, 400);
	spr_encrypt.setPosition(600, 400);

	//used to compare the positions of each character
	char character_array[26] = { 'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	while (window.isOpen()) //continue running until the user closes the window
	{
		sf::Event event;
		window.clear(); //clear the screen for the next frame
		for (int i = 0; i < 9; i++) //draw the texture in the background
		{
			for (int j = 0; j < 9; j++)
			{
				back_wall.setPosition(100 * i, 100 * j);
				back_wall2.setPosition(100 * i + 50, 100 * j);
				window.draw(back_wall);
				window.draw(back_wall2);

				back_wall2.setPosition(100 * i, 100 * j + 50);
				back_wall.setPosition(100 * i + 50, 100 * j + 50);
				window.draw(back_wall);
				window.draw(back_wall2);
			}
		}
		
		
		

		shift_num.setPosition(65, 375); //draw the number of the shift value and change its size if needed
		if (shift_counter > 9 || shift_counter < -9)
		{
			shift_num.setCharacterSize(32);
		}
		else
		{
			shift_num.setCharacterSize(48);
		} 
		shift_num.setString(to_string(shift_counter)); //set the text to the correct number
		

		while (window.pollEvent(event)) //check for user input
		{
			if (event.type == sf::Event::Closed) //if user closes the window
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) //if user clicked the mouse inside the window
			{
				//capture mouse position and check if it clicking certain sprites
				auto mouse_pos = sf::Mouse::getPosition(window);
				auto translated_pos = window.mapPixelToCoords(mouse_pos);
				if (spr_arrowup.getGlobalBounds().contains(translated_pos)) //increment the shift value if the up arrow is clicked
				{
					shift_counter++;
				}
				else if (spr_arrowdown.getGlobalBounds().contains(translated_pos)) //decrement the shift value if the down arrow is clicked
				{
					shift_counter--;
				}
				else if (spr_erase.getGlobalBounds().contains(translated_pos)) //erase the entered text if the erase sprite is clicked
				{
					user_input = "";
					user_text.setString("");
					char_vector.clear();
					encrpyted_text.setString("");
				}
				else if (spr_encrypt.getGlobalBounds().contains(translated_pos)) //encrypt the text the user has entered if the encrypt sprite is clicked
				{
					encrpyted_text.setString(""); 
					string new_string = "";
					//for each character in the entered text, shift it up or down by the shift value. If it exceeds the length of the alphabet, loop it back to the other end.
					for (int i = 0; i < char_vector.size(); i++)
					{
						int new_char = 0;
						for (int j = 0; j < 26; j++)
						{
							
							if (char_vector[i] == character_array[j])
							{
								new_char = j + shift_counter;
							}
							if (new_char > 25)
							{
								new_char -= 26;
							}
							else if (new_char < 0)
							{
								new_char += 26;
							}
							
						}
						new_string += character_array[new_char];
					}
					encrpyted_text.setString(new_string);
				}
			}
			else if (event.type == sf::Event::TextEntered) //the user pressed a key
			{
				if (find(begin(character_array), end(character_array), event.text.unicode) != end(character_array)) //if the key pressed was a lowercase letter
				{
					if (user_input.getSize() < 16) //limit the input to 16 characters
					{
						user_input += event.text.unicode;
						user_text.setString(user_input);
						char_vector.push_back(event.text.unicode);
						
					}
				}
			}
		}
		
		//DRAW SPRITES TO THE WINDOW AND DISPLAY

		spr_typebox1.setPosition(290, 250);
		spr_typebox3.setPosition(770, 250);
		for (int i = 330; i < 770; i += 40)
		{
			spr_typebox2.setPosition(i, 250);
			window.draw(spr_typebox2);
		}
		window.draw(spr_typebox1);
		window.draw(spr_typebox3);

		spr_typebox1.setPosition(290, 600);
		spr_typebox3.setPosition(770, 600);
		for (int i = 330; i < 770; i += 40)
		{
			spr_typebox2.setPosition(i, 600);
			window.draw(spr_typebox2);
		}
		window.draw(spr_typebox3);
		window.draw(spr_typebox1);
		window.draw(spr_textbox);
		window.draw(spr_arrowup);
		window.draw(spr_arrowdown);
		window.draw(spr_erase);
		window.draw(spr_encrypt);
		window.draw(erase_text);
		window.draw(Encrypt_text);
		window.draw(user_text);
		window.draw(encrpyted_text);
		window.draw(shift_num);
		window.draw(title_string);
		window.draw(subtitle_string1);
		window.draw(subtitle_string2);
		window.draw(subtitle_string3);
		window.display();
	}
}


void Vigenere()
{

	sf::RenderWindow window(sf::VideoMode(1050, 1050), "Vigenere Cypher");

	sf::Font font; //import font for text
	if (!font.loadFromFile("arial.ttf"))
	{
		//error
		cout << "ERROR!" << endl;
	}

	//CREATE AND CONFIGURE SPRITES USED

	sf::Text title_string;
	title_string.setFillColor(sf::Color::White);
	title_string.setFont(font);
	title_string.setCharacterSize(48);
	title_string.setPosition(25, 25);
	title_string.setString("Vigenere Cypher");

	sf::Text subtitle_string1;
	subtitle_string1.setFillColor(sf::Color::White);
	subtitle_string1.setFont(font);
	subtitle_string1.setCharacterSize(18);
	subtitle_string1.setPosition(25, 100);
	subtitle_string1.setString("Encrpytion: \n 1) Choose a word to act as a key. \n 2) Loop the key until it is equal in size to the text. \n 3) Find the first characters of the text and key \n \
    on the outermost row and column (blue highlight). \n     The first character of the cypher text is the \n     value in which the row and column intersect \n     on the grid. \n 4) Move onto the next character in the \n \
    plaintext and key, and repeat steps 3-4 until \n     every character is encrypted.");

	sf::Text subtitle_string2;
	subtitle_string2.setFillColor(sf::Color::White);
	subtitle_string2.setFont(font);
	subtitle_string2.setCharacterSize(18);
	subtitle_string2.setPosition(25, 625);
	subtitle_string2.setString("Decryption: \n 1) Locate the first character of the key in the \n     grids left key line. \n 2) In that row, locate the character that matches \n \
    the first line of the cyphertext. \n 3) Whatever character in the grids upper key line \n     that lines up with the identified character is \n     the decrypted character. \n 4) \
Move onto the second character in the \n     cyphertext and key, and repeat until every \n     character is decrypted.");

	sf::Text subtitle_string3;
	subtitle_string3.setFillColor(sf::Color::White);
	subtitle_string3.setFont(font);
	subtitle_string3.setCharacterSize(18);
	subtitle_string3.setPosition(50, 900);
	subtitle_string3.setString("Security: Allows for X   potential combinations, Where X is the length of the alphabet used \n               and K is the length of the unlooped key.");

	sf::Text subtitle_string4;
	subtitle_string4.setFillColor(sf::Color::White);
	subtitle_string4.setFont(font);
	subtitle_string4.setCharacterSize(12);
	subtitle_string4.setPosition(223, 895);
	subtitle_string4.setString("K");

	bool text_or_key = 0;

	sf::String user_input;
	sf::Text user_text;
	user_text.setFillColor(sf::Color::Black);
	user_text.setFont(font);
	user_text.setCharacterSize(48);
	user_text.setPosition(460, 50);
	vector<char> char_vector;

	sf::String user_input2;
	sf::Text user_text2;
	user_text2.setFillColor(sf::Color::Black);
	user_text2.setFont(font);
	user_text2.setCharacterSize(48);
	user_text2.setPosition(460, 150);
	vector<char> char_vector2;

	sf::Text encrpyted_text;
	encrpyted_text.setFillColor(sf::Color::Black);
	encrpyted_text.setFont(font);
	encrpyted_text.setCharacterSize(48);
	encrpyted_text.setPosition(460, 800);

	sf::Text erase_text;
	erase_text.setFont(font);
	erase_text.setString("Erase \n Text");
	erase_text.setCharacterSize(30);
	erase_text.setFillColor(sf::Color::Black);
	erase_text.setPosition(170, 410);

	sf::Text erase_text2;
	erase_text2.setFont(font);
	erase_text2.setString("Erase \n Key");
	erase_text2.setCharacterSize(30);
	erase_text2.setFillColor(sf::Color::Black);
	erase_text2.setPosition(170, 510);

	sf::Text Enter_text;
	Enter_text.setFont(font);
	Enter_text.setString("Enter \n Text");
	Enter_text.setCharacterSize(30);
	Enter_text.setFillColor(sf::Color::Black);
	Enter_text.setPosition(70, 410);

	sf::Text Enter_key;
	Enter_key.setFont(font);
	Enter_key.setString("Enter \n key");
	Enter_key.setCharacterSize(30);
	Enter_key.setFillColor(sf::Color::Black);
	Enter_key.setPosition(70, 510);

	sf::Text Encrypt_text;
	Encrypt_text.setFont(font);
	Encrypt_text.setString("Encrypt");
	Encrypt_text.setCharacterSize(20);
	Encrypt_text.setFillColor(sf::Color::Black);
	Encrypt_text.setPosition(270, 435);

	sf::Text Decrypt_text;
	Decrypt_text.setFont(font);
	Decrypt_text.setString("Decrypt");
	Decrypt_text.setCharacterSize(20);
	Decrypt_text.setFillColor(sf::Color::Black);
	Decrypt_text.setPosition(270, 535);

	sf::Text grid_text;
	grid_text.setFont(font);
	grid_text.setCharacterSize(20);
	grid_text.setFillColor(sf::Color::White);

	sf::RectangleShape back_wall;
	back_wall.setSize(sf::Vector2f(50, 50));
	back_wall.setFillColor(sf::Color::Color(25, 25, 25));

	sf::RectangleShape back_wall2;
	back_wall2.setSize(sf::Vector2f(50, 50));
	back_wall2.setFillColor(sf::Color::Color(50, 50, 50));

	sf::RectangleShape grid_lines;
	grid_lines.setSize(sf::Vector2f(1, 540));
	grid_lines.setFillColor(sf::Color::Color(200, 200, 200));

	sf::Texture textbox;
	if (!textbox.loadFromFile("Textbox.png"))
	{
		//Error
		cout << "Error!" << endl;
	}

	sf::Sprite spr_typebox1;
	spr_typebox1.setTexture(textbox);
	spr_typebox1.setTextureRect(sf::IntRect(0, 0, 40, 64));

	sf::Sprite spr_typebox2;
	spr_typebox2.setTexture(textbox);
	spr_typebox2.setTextureRect(sf::IntRect(10, 0, 40, 64));

	sf::Sprite spr_typebox3;
	spr_typebox3.setTexture(textbox);
	spr_typebox3.setTextureRect(sf::IntRect(10, 0, 64, 64));

	sf::Sprite spr_erase;
	spr_erase.setTexture(textbox);
	spr_erase.scale(sf::Vector2f(1.5f, 1.5f));

	sf::Sprite spr_erase2;
	spr_erase2.setTexture(textbox);
	spr_erase2.scale(sf::Vector2f(1.5f, 1.5f));

	sf::Sprite spr_encrypt;
	spr_encrypt.setTexture(textbox);
	spr_encrypt.scale(sf::Vector2f(1.5f, 1.5f));

	spr_erase.setPosition(160, 400);
	spr_encrypt.setPosition(260, 400);
	spr_erase2.setPosition(160, 500);

	sf::Sprite spr_typeText;
	spr_typeText.setTexture(textbox);
	spr_typeText.scale(sf::Vector2f(1.5f, 1.5f));

	sf::Sprite spr_typeKey;
	spr_typeKey.setTexture(textbox);
	spr_typeKey.scale(sf::Vector2f(1.5f, 1.5f));

	spr_typeText.setPosition(60, 400);
	spr_typeKey.setPosition(60, 500);

	sf::Sprite spr_decrypt;
	spr_decrypt.setTexture(textbox);
	spr_decrypt.scale(sf::Vector2f(1.5f, 1.5f));
	spr_decrypt.setPosition(260, 500);

	//character_array contains all the letters of the alphabet, character_matrix then uses the array to create a table of characters, with the starting letter offset by the row number
	char character_array[26] = { 'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char character_matrix[26][26];
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			int k = i + j;
			if (k >= 26)
			{
				k -= 26;
			}
			character_matrix[i][j] = toupper(character_array[k]);
		}
	}
	while (window.isOpen()) //while window is open
	{
		sf::Event event;
		window.clear(); //clear sprites for the next frame
		for (int i = 0; i < 11; i++) //draw the background
		{
			for (int j = 0; j < 11; j++)
			{
				back_wall.setPosition(100 * i, 100 * j);
				back_wall2.setPosition(100 * i + 50, 100 * j);
				window.draw(back_wall);
				window.draw(back_wall2);

				back_wall2.setPosition(100 * i, 100 * j + 50);
				back_wall.setPosition(100 * i + 50, 100 * j + 50);
				window.draw(back_wall);
				window.draw(back_wall2);
			}
		}

		for (int i = 0; i < 26; i++) //draw the character_matrix to the window, and add gridlines
		{
			grid_text.setFillColor(sf::Color::Color(100, 100, 200));
			grid_text.setString(character_matrix[i][0]);
			grid_text.setPosition(470 + i * 20, 220);
			window.draw(grid_text);
			grid_text.setString(character_matrix[i][0]);
			grid_text.setPosition(450, 240 + i * 20);
			window.draw(grid_text);
			grid_text.setFillColor(sf::Color::White);
			
			grid_lines.setPosition(467 + i * 20, 220);
			window.draw(grid_lines);
			grid_lines.setRotation(270.f);
			grid_lines.setPosition(450, 242 + i * 20);
			window.draw(grid_lines);
			grid_lines.setRotation(0.f);
			for (int j = 0; j < 26; j++)
			{
				grid_text.setString(character_matrix[i][j]);
				grid_text.setPosition(470 + i * 20, 240 + j * 20);
				window.draw(grid_text);

			}
		}
		grid_lines.setPosition(990, 220);
		window.draw(grid_lines);
		grid_lines.setRotation(270.f);
		grid_lines.setPosition(450, 763);
		window.draw(grid_lines);
		grid_lines.setRotation(0.f);

		while (window.pollEvent(event)) //check for user input
		{
			if (event.type == sf::Event::Closed) //user closed window
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) //user clicked mouse
			{
				//get click position in window and execute code if the corresponding sprite was clicked
				auto mouse_pos = sf::Mouse::getPosition(window);
				auto translated_pos = window.mapPixelToCoords(mouse_pos);
				if (spr_erase.getGlobalBounds().contains(translated_pos))
				{
					user_input = "";
					user_text.setString("");
					char_vector.clear();
					encrpyted_text.setString("");
				}
				else if (spr_erase2.getGlobalBounds().contains(translated_pos))
				{
					user_input2 = "";
					user_text2.setString("");
					char_vector2.clear();
					encrpyted_text.setString("");
				}
				else if (spr_encrypt.getGlobalBounds().contains(translated_pos))
				{
					//run the Viginere algorithm
					encrpyted_text.setString("");
					string new_string = "";

					if (user_input2 != "")
					{
						for (int i = 0; i < user_input.getSize(); i++) //for each character in the user input
						{
							string looped_key = user_input2; 
							while (looped_key.size() < user_input.getSize()) //append key string to itself until it is equal or greater length to the plaintext
							{
								looped_key += looped_key;
							}
							while (looped_key.size() > user_input.getSize()) //if key is larger than plaintext, removal final character until they are equal in size
							{
								looped_key.pop_back();
							}
							bool found_row = false;
							int row = 0;
							while (!found_row) //search for the correct row in the grid
							{
								if (character_array[row] == char_vector[i])
								{
									found_row = true;
								}
								else
								{
									row++;
								}
							}
							bool found_column = false;
							int column = 0;
							while (!found_column) //search for the correct column in the grid
							{
								if (character_array[column] == looped_key[i])
								{
									found_column = true;
								}
								else
								{
									column++;
								}

							}
							new_string += tolower(character_matrix[row][column]); //find the character in the coordinates found
						}
						encrpyted_text.setString(new_string); //append the new character to the output
					}
				}
				else if (spr_typeText.getGlobalBounds().contains(translated_pos))
				{
					text_or_key = 0;
				}
				else if (spr_typeKey.getGlobalBounds().contains(translated_pos))
				{
					text_or_key = 1;
				}
				else if (spr_decrypt.getGlobalBounds().contains(translated_pos))
				{
					encrpyted_text.setString("");
					string new_string = "";

					if (user_input2 != "")
					{
						string looped_key = user_input2;
						while (looped_key.size() < user_input.getSize()) //append key to itself until equal or greater in size to the cyphertext
						{
							looped_key += looped_key;
						}
						while (looped_key.size() > user_input.getSize()) //reduce key length to be equal to cyphertext length
						{
							looped_key.pop_back();
						}
						for (int i = 0; i < user_input.getSize(); i++) //for each character in cyphertext
						{
							bool found_row = false;
							int row = 0;
							while (!found_row) //search for correct row
							{
								if (character_array[row] == looped_key[i])
								{
									found_row = true;
								}
								else
								{
									row++;
								}
							}
							bool found_column = false;
							int column = 0;
							while (!found_column) //search for correct column
							{
								if (character_matrix[row][column] == toupper(char_vector[i]))
								{
									
									found_column = true;
								}
								else
								{
									column++;
								}

							}
							new_string += character_array[column]; //find the corresponding character in the grid
							
						}
						encrpyted_text.setString(new_string); //append found character to output
					}
				}
			}
			else if (event.type == sf::Event::TextEntered) //if a key was pressed
			{
				if (find(begin(character_array), end(character_array), event.text.unicode) != end(character_array)) //check if valid keypress
				{
					if (text_or_key == 0) //if user is entering plaintext/cyphertext
					{
						if (user_input.getSize() < 16) //allow up to 16 characters
						{
							user_input += event.text.unicode;
							user_text.setString(user_input);
							char_vector.push_back(event.text.unicode);

						}
					}
					else //user is entering key
					{
						
						if (user_input2.getSize() < 16) //allow up to 16 characters
						{
							user_input2 += event.text.unicode;
							user_text2.setString(user_input2);
							char_vector2.push_back(event.text.unicode);

						}
					}
					
				}
			}
		}

		//DRAW SPRITES TO WINDOW AND DISPLAY

		spr_typebox1.setPosition(450, 50);
		spr_typebox3.setPosition(920, 50);
		for (int i = 450; i < 920; i += 40)
		{
			spr_typebox2.setPosition(i, 50);
			window.draw(spr_typebox2);
		}
		window.draw(spr_typebox1);
		window.draw(spr_typebox3);

		spr_typebox1.setPosition(450, 150);
		spr_typebox3.setPosition(920, 150);
		for (int i = 450; i < 920; i += 40)
		{
			spr_typebox2.setPosition(i, 150);
			window.draw(spr_typebox2);
		}
		window.draw(spr_typebox1);
		window.draw(spr_typebox3);

		spr_typebox1.setPosition(450, 800);
		spr_typebox3.setPosition(920, 800);
		for (int i = 480; i < 920; i += 40)
		{
			spr_typebox2.setPosition(i, 800);
			window.draw(spr_typebox2);
		}

		window.draw(spr_typebox3);
		window.draw(spr_typebox1);
		window.draw(spr_erase);
		window.draw(spr_encrypt);
		window.draw(spr_typeText);
		window.draw(spr_typeKey);
		window.draw(spr_erase2);
		window.draw(spr_decrypt);
		window.draw(Enter_text);
		window.draw(Enter_key);
		window.draw(erase_text);
		window.draw(erase_text2);
		window.draw(Encrypt_text);
		window.draw(Decrypt_text);
		window.draw(user_text);
		window.draw(user_text2);
		window.draw(encrpyted_text);
		window.draw(title_string);
		window.draw(subtitle_string1);
		window.draw(subtitle_string2);
		window.draw(subtitle_string3);
		window.draw(subtitle_string4);
		window.display();
	}
}


void Enigma_cypher()
{
	sf::RenderWindow window(sf::VideoMode(1050, 1050), "Enigma Cypher"); //create the window
	sf::Font font; //import font for text
	if (!font.loadFromFile("arial.ttf"))
	{
		//error
		cout << "ERROR!" << endl;
	}

	//CREATE AND CONFIGURE SPRITES AND VARIABLES

	sf::Text title_string;
	title_string.setFillColor(sf::Color::White);
	title_string.setFont(font);
	title_string.setCharacterSize(48);
	title_string.setPosition(25, 25);
	title_string.setString("Enigma Cypher");

	sf::Text subtitle_string1;
	subtitle_string1.setFillColor(sf::Color::White);
	subtitle_string1.setFont(font);
	subtitle_string1.setCharacterSize(18);
	subtitle_string1.setPosition(10, 200);
	subtitle_string1.setString("Current Rotor configuration: ");

	sf::Text subtitle_string2;
	subtitle_string2.setFillColor(sf::Color::White);
	subtitle_string2.setFont(font);
	subtitle_string2.setCharacterSize(18);
	subtitle_string2.setPosition(10, 275);
	subtitle_string2.setString("Output: ");

	sf::Text subtitle_string3;
	subtitle_string3.setFillColor(sf::Color::White);
	subtitle_string3.setFont(font);
	subtitle_string3.setCharacterSize(18);
	subtitle_string3.setPosition(10, 675);
	subtitle_string3.setString("Plugboard configuration: ");

	sf::String user_input;
	sf::Text user_text;
	user_text.setFillColor(sf::Color::Black);
	user_text.setFont(font);
	user_text.setCharacterSize(48);
	user_text.setPosition(140, 100);
	vector<char> char_vector;

	sf::Text encrpyted_text;
	encrpyted_text.setFillColor(sf::Color::Black);
	encrpyted_text.setFont(font);
	encrpyted_text.setCharacterSize(48);
	encrpyted_text.setPosition(460, 800);

	sf::Text erase_text;
	erase_text.setFont(font);
	erase_text.setString("Erase \n Text");
	erase_text.setCharacterSize(30);
	erase_text.setFillColor(sf::Color::Black);
	erase_text.setPosition(170, 410);

	sf::RectangleShape back_wall;
	back_wall.setSize(sf::Vector2f(50, 50));
	back_wall.setFillColor(sf::Color::Color(25, 25, 25));

	sf::RectangleShape back_wall2;
	back_wall2.setSize(sf::Vector2f(50, 50));
	back_wall2.setFillColor(sf::Color::Color(50, 50, 50));

	sf::Texture textbox;
	if (!textbox.loadFromFile("Textbox.png"))
	{
		//Error
		cout << "Error!" << endl;
	}

	sf::Sprite spr_typebox1;
	spr_typebox1.setTexture(textbox);
	spr_typebox1.setTextureRect(sf::IntRect(0, 0, 40, 64));

	sf::Sprite spr_typebox2;
	spr_typebox2.setTexture(textbox);
	spr_typebox2.setTextureRect(sf::IntRect(10, 0, 40, 64));

	sf::Sprite spr_typebox3;
	spr_typebox3.setTexture(textbox);
	spr_typebox3.setTextureRect(sf::IntRect(10, 0, 64, 64));

	sf::Sprite spr_erase;
	spr_erase.setTexture(textbox);
	spr_erase.setPosition(158, 600);

	sf::Text txt_erase_text;
	txt_erase_text.setFont(font);
	txt_erase_text.setString("Erase\nText");
	txt_erase_text.setCharacterSize(18);
	txt_erase_text.setFillColor(sf::Color::Black);
	txt_erase_text.setPosition(165, 610);

	sf::Sprite spr_erase_plugs;
	spr_erase_plugs.setTexture(textbox);
	spr_erase_plugs.setPosition(83, 600);

	sf::Text txt_erase;
	txt_erase.setFont(font);
	txt_erase.setString("Reset\n Plugs");
	txt_erase.setCharacterSize(18);
	txt_erase.setFillColor(sf::Color::Black);
	txt_erase.setPosition(90, 610);

	sf::Sprite spr_configure_plugs;
	spr_configure_plugs.setTexture(textbox);
	spr_configure_plugs.setPosition(10, 600);

	sf::Text txt_configure_plugs;
	txt_configure_plugs.setFont(font);
	txt_configure_plugs.setString("Set\nPlug");
	txt_configure_plugs.setCharacterSize(18);
	txt_configure_plugs.setFillColor(sf::Color::Black);
	txt_configure_plugs.setPosition(23, 610);

	bool setplug = false;
	bool firstPlugEntered = false;
	char firstplug = '1';
	char secondplug = '2';

	sf::Sprite spr_rotor1;
	spr_rotor1.setTexture(textbox);
	spr_rotor1.scale(sf::Vector2f(1.0f, 1.0f));
	spr_rotor1.setPosition(300, 200);

	sf::Sprite spr_rotor2;
	spr_rotor2.setTexture(textbox);
	spr_rotor2.scale(sf::Vector2f(1.0f, 1.0f));
	spr_rotor2.setPosition(450, 200);

	sf::Sprite spr_rotor3;
	spr_rotor3.setTexture(textbox);
	spr_rotor3.scale(sf::Vector2f(1.0f, 1.0f));
	spr_rotor3.setPosition(600, 200);

	sf::Sprite spr_change_rotor1;
	spr_change_rotor1.setTexture(textbox);
	spr_change_rotor1.scale(sf::Vector2f(0.5f, 0.5f));
	spr_change_rotor1.setPosition(250, 230);

	sf::Sprite spr_change_rotor2;
	spr_change_rotor2.setTexture(textbox);
	spr_change_rotor2.scale(sf::Vector2f(0.5f, 0.5f));
	spr_change_rotor2.setPosition(400, 230);

	sf::Sprite spr_change_rotor3;
	spr_change_rotor3.setTexture(textbox);
	spr_change_rotor3.scale(sf::Vector2f(0.5f, 0.5f));
	spr_change_rotor3.setPosition(550, 230);

	sf::Text txt_rotor1;
	char char_rotor1 = 'A';
	txt_rotor1.setFont(font);
	txt_rotor1.setString(char_rotor1);
	txt_rotor1.setCharacterSize(42);
	txt_rotor1.setFillColor(sf::Color::Black);
	txt_rotor1.setPosition(317, 205);

	sf::Text txt_rotor2;
	char char_rotor2 = 'A';
	txt_rotor2.setFont(font);
	txt_rotor2.setString(char_rotor1);
	txt_rotor2.setCharacterSize(42);
	txt_rotor2.setFillColor(sf::Color::Black);
	txt_rotor2.setPosition(467, 205);

	sf::Text txt_rotor3;
	char char_rotor3 = 'A';
	txt_rotor3.setFont(font);
	txt_rotor3.setString(char_rotor1);
	txt_rotor3.setCharacterSize(42);
	txt_rotor3.setFillColor(sf::Color::Black);
	txt_rotor3.setPosition(617, 205);

	sf::Text txt_change_rotor1;
	char char_change_rotor1 = '1';
	txt_change_rotor1.setFont(font);
	txt_change_rotor1.setString(char_change_rotor1);
	txt_change_rotor1.setCharacterSize(24);
	txt_change_rotor1.setFillColor(sf::Color::Black);
	txt_change_rotor1.setPosition(258, 230);

	sf::Text txt_change_rotor2;
	char char_change_rotor2 = '2';
	txt_change_rotor2.setFont(font);
	txt_change_rotor2.setString(char_change_rotor2);
	txt_change_rotor2.setCharacterSize(24);
	txt_change_rotor2.setFillColor(sf::Color::Black);
	txt_change_rotor2.setPosition(408, 230);

	sf::Text txt_change_rotor3;
	char char_change_rotor3 = '3';
	txt_change_rotor3.setFont(font);
	txt_change_rotor3.setString(char_change_rotor3);
	txt_change_rotor3.setCharacterSize(24);
	txt_change_rotor3.setFillColor(sf::Color::Black);
	txt_change_rotor3.setPosition(558, 230);

	sf::Text txt_enter_plug;
	txt_enter_plug.setFont(font);
	txt_enter_plug.setString("");
	txt_enter_plug.setCharacterSize(18);
	txt_enter_plug.setPosition(300, 625);

	sf::Texture letters;
	if (!letters.loadFromFile("Letters.png"))
	{
		//Error
		cout << "Error!" << endl;
	}

	vector<sf::Sprite> sprite_vector; //create a empty vector of sprites

	//create each sprite using imported spritesheet (Letters.png). Configure their positions on the screen in a loop
	int x_line = -64;
	int y_line = 0;
	int sprite_fixer = 0;
	int sprite_fixer2 = 0;
	for (int i = 0; i < 26; i++)
	{
		x_line += 64;
		if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25)
		{
			x_line -= 64 * 5;
			y_line += 64;
			sprite_fixer = 0;
			sprite_fixer2++;
		}
		sf::Sprite spr_letters; //create a new sprite and configure it
		spr_letters.setTexture(letters);
		//spr_letters.setPosition(200 + x_line, 600 + y_line);
		spr_letters.setColor(sf::Color(128, 128, 128));
		spr_letters.setTextureRect(sf::IntRect(x_line, y_line, x_line + (64 - (64 * sprite_fixer)), y_line + (64 - (64 * sprite_fixer2))));

		sprite_vector.push_back(spr_letters); //push new sprite onto the vector
		sprite_fixer++;
		
	}
	//configure each sprites position on the screen
	sprite_vector[16].setPosition(100, 300);
	sprite_vector[22].setPosition(200, 300);
	sprite_vector[4].setPosition(300, 300);
	sprite_vector[17].setPosition(400, 300);
	sprite_vector[19].setPosition(500, 300);
	sprite_vector[25].setPosition(600, 300);
	sprite_vector[20].setPosition(700, 300);
	sprite_vector[8].setPosition(800, 300);
	sprite_vector[14].setPosition(900, 300);

	sprite_vector[0].setPosition(150, 400);
	sprite_vector[18].setPosition(250, 400);
	sprite_vector[3].setPosition(350, 400);
	sprite_vector[5].setPosition(450, 400);
	sprite_vector[6].setPosition(550, 400);
	sprite_vector[7].setPosition(650, 400);
	sprite_vector[9].setPosition(750, 400);
	sprite_vector[10].setPosition(850, 400);

	sprite_vector[15].setPosition(100, 500);
	sprite_vector[24].setPosition(200, 500);
	sprite_vector[23].setPosition(300, 500);
	sprite_vector[2].setPosition(400, 500);
	sprite_vector[21].setPosition(500, 500);
	sprite_vector[1].setPosition(600, 500);
	sprite_vector[13].setPosition(700, 500);
	sprite_vector[12].setPosition(800, 500);
	sprite_vector[11].setPosition(900, 500);


	vector<sf::Sprite> plugboard_sprite_vector; //same steps as the above sprite vector

	x_line = -64;
	y_line = 0;
	sprite_fixer = 0;
	sprite_fixer2 = 0;
	for (int i = 0; i < 26; i++)
	{
		x_line += 64;
		if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25)
		{
			x_line -= 64 * 5;
			y_line += 64;
			sprite_fixer = 0;
			sprite_fixer2++;
		}
		sf::Sprite spr_letters;
		spr_letters.setTexture(letters);
		//spr_letters.setPosition(200 + x_line, 600 + y_line);
		spr_letters.setColor(sf::Color(92, 92, 92));
		spr_letters.setTextureRect(sf::IntRect(x_line, y_line, x_line + (64 - (64 * sprite_fixer)), y_line + (64 - (64 * sprite_fixer2))));

		plugboard_sprite_vector.push_back(spr_letters);
		sprite_fixer++;

	}
	plugboard_sprite_vector[16].setPosition(100, 700);
	plugboard_sprite_vector[22].setPosition(200, 700);
	plugboard_sprite_vector[4].setPosition(300, 700);
	plugboard_sprite_vector[17].setPosition(400, 700);
	plugboard_sprite_vector[19].setPosition(500, 700);
	plugboard_sprite_vector[25].setPosition(600, 700);
	plugboard_sprite_vector[20].setPosition(700, 700);
	plugboard_sprite_vector[8].setPosition(800, 700);
	plugboard_sprite_vector[14].setPosition(900, 700);

	plugboard_sprite_vector[0].setPosition(150, 800);
	plugboard_sprite_vector[18].setPosition(250, 800);
	plugboard_sprite_vector[3].setPosition(350, 800);
	plugboard_sprite_vector[5].setPosition(450, 800);
	plugboard_sprite_vector[6].setPosition(550, 800);
	plugboard_sprite_vector[7].setPosition(650, 800);
	plugboard_sprite_vector[9].setPosition(750, 800);
	plugboard_sprite_vector[10].setPosition(850, 800);

	plugboard_sprite_vector[15].setPosition(100, 900);
	plugboard_sprite_vector[24].setPosition(200, 900);
	plugboard_sprite_vector[23].setPosition(300, 900);
	plugboard_sprite_vector[2].setPosition(400, 900);
	plugboard_sprite_vector[21].setPosition(500, 900);
	plugboard_sprite_vector[1].setPosition(600, 900);
	plugboard_sprite_vector[13].setPosition(700, 900);
	plugboard_sprite_vector[12].setPosition(800, 900);
	plugboard_sprite_vector[11].setPosition(900, 900);

	vector<sf::Color> colour_vector; //a vector of colours used to colour the sprites later
	colour_vector.push_back(sf::Color::Color(255, 255, 0));
	colour_vector.push_back(sf::Color::Color(255, 0, 255));
	colour_vector.push_back(sf::Color::Color(0, 255, 255));
	colour_vector.push_back(sf::Color::Color(255, 0, 0));
	colour_vector.push_back(sf::Color::Color(0, 255, 0));
	colour_vector.push_back(sf::Color::Color(0, 0, 255));
	colour_vector.push_back(sf::Color::Color(96, 96, 0));
	colour_vector.push_back(sf::Color::Color(96, 0, 96));
	colour_vector.push_back(sf::Color::Color(0, 96, 96));
	colour_vector.push_back(sf::Color::Color(96, 0, 0));
	colour_vector.push_back(sf::Color::Color(0, 0, 96));
	colour_vector.push_back(sf::Color::Color(0, 96, 0));
	colour_vector.push_back(sf::Color::Color(255, 255, 255));
	int colour_counter = 0; 

	bool key_pressed = false; //check if a key is being pressed
	vector<int> current_rotors; //keeps track of what rotors are currently selected
	current_rotors.push_back(1);
	current_rotors.push_back(2);
	current_rotors.push_back(3);
	char character_array[26] = { 'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	int current_key_pressed = -1;
	char first_character_entered = ' ';
	int spacer = -1; //used to space out the text into groups of 5

	Enigma enigmaMachine; //create an Enigma object
	while (window.isOpen()) //while the window is open
	{
		sf::Event event;
		window.clear(); //clear the window
		for (int i = 0; i < 11; i++) //draw background
		{
			for (int j = 0; j < 11; j++)
			{
				back_wall.setPosition(100 * i, 100 * j);
				back_wall2.setPosition(100 * i + 50, 100 * j);
				window.draw(back_wall);
				window.draw(back_wall2);

				back_wall2.setPosition(100 * i, 100 * j + 50);
				back_wall.setPosition(100 * i + 50, 100 * j + 50);
				window.draw(back_wall);
				window.draw(back_wall2);
			}
		}

		while (window.pollEvent(event)) //chheck for user input
		{
			if (event.type == sf::Event::Closed) //if user closes the window
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) //if user clicks
			{
				//get click position and check which sprite was clicked
				auto mouse_pos = sf::Mouse::getPosition(window);
				auto translated_pos = window.mapPixelToCoords(mouse_pos);
				if (spr_erase.getGlobalBounds().contains(translated_pos)) //erase displayed text
				{
					user_input = "";
					user_text.setString("");
					char_vector.clear();
					encrpyted_text.setString("");
				}
				else if (spr_rotor1.getGlobalBounds().contains(translated_pos)) //increment the value of the rotor in position 1
				{
					
					switch (char_rotor1)
					{
					case 'A': char_rotor1 = 'B'; txt_rotor1.setString('B'); enigmaMachine.setRotors(current_rotors[0], 1, 0); break;
					case 'B': char_rotor1 = 'C'; txt_rotor1.setString('C'); enigmaMachine.setRotors(current_rotors[0], 2, 0); break;
					case 'C': char_rotor1 = 'D'; txt_rotor1.setString('D'); enigmaMachine.setRotors(current_rotors[0], 3, 0); break;
					case 'D': char_rotor1 = 'E'; txt_rotor1.setString('E'); enigmaMachine.setRotors(current_rotors[0], 4, 0); break;
					case 'E': char_rotor1 = 'F'; txt_rotor1.setString('F'); enigmaMachine.setRotors(current_rotors[0], 5, 0); break;
					case 'F': char_rotor1 = 'G'; txt_rotor1.setString('G'); enigmaMachine.setRotors(current_rotors[0], 6, 0); break;
					case 'G': char_rotor1 = 'H'; txt_rotor1.setString('H'); enigmaMachine.setRotors(current_rotors[0], 7, 0); break;
					case 'H': char_rotor1 = 'I'; txt_rotor1.setString('I'); enigmaMachine.setRotors(current_rotors[0], 8, 0); break;
					case 'I': char_rotor1 = 'J'; txt_rotor1.setString('J'); enigmaMachine.setRotors(current_rotors[0], 9, 0); break;
					case 'J': char_rotor1 = 'K'; txt_rotor1.setString('K'); enigmaMachine.setRotors(current_rotors[0], 10, 0); break;
					case 'K': char_rotor1 = 'L'; txt_rotor1.setString('L'); enigmaMachine.setRotors(current_rotors[0], 11, 0); break;
					case 'L': char_rotor1 = 'M'; txt_rotor1.setString('M'); enigmaMachine.setRotors(current_rotors[0], 12, 0); break;
					case 'M': char_rotor1 = 'N'; txt_rotor1.setString('N'); enigmaMachine.setRotors(current_rotors[0], 13, 0); break;
					case 'N': char_rotor1 = 'O'; txt_rotor1.setString('O'); enigmaMachine.setRotors(current_rotors[0], 14, 0); break;
					case 'O': char_rotor1 = 'P'; txt_rotor1.setString('P'); enigmaMachine.setRotors(current_rotors[0], 15, 0); break;
					case 'P': char_rotor1 = 'Q'; txt_rotor1.setString('Q'); enigmaMachine.setRotors(current_rotors[0], 16, 0); break;
					case 'Q': char_rotor1 = 'R'; txt_rotor1.setString('R'); enigmaMachine.setRotors(current_rotors[0], 17, 0); break;
					case 'R': char_rotor1 = 'S'; txt_rotor1.setString('S'); enigmaMachine.setRotors(current_rotors[0], 18, 0); break;
					case 'S': char_rotor1 = 'T'; txt_rotor1.setString('T'); enigmaMachine.setRotors(current_rotors[0], 19, 0); break;
					case 'T': char_rotor1 = 'U'; txt_rotor1.setString('U'); enigmaMachine.setRotors(current_rotors[0], 20, 0); break;
					case 'U': char_rotor1 = 'V'; txt_rotor1.setString('V'); enigmaMachine.setRotors(current_rotors[0], 21, 0); break;
					case 'V': char_rotor1 = 'W'; txt_rotor1.setString('W'); enigmaMachine.setRotors(current_rotors[0], 22, 0); break;
					case 'W': char_rotor1 = 'X'; txt_rotor1.setString('X'); enigmaMachine.setRotors(current_rotors[0], 23, 0); break;
					case 'X': char_rotor1 = 'Y'; txt_rotor1.setString('Y'); enigmaMachine.setRotors(current_rotors[0], 24, 0); break;
					case 'Y': char_rotor1 = 'Z'; txt_rotor1.setString('Z'); enigmaMachine.setRotors(current_rotors[0], 25, 0); break;
					case 'Z': char_rotor1 = 'A'; txt_rotor1.setString('A'); enigmaMachine.setRotors(current_rotors[0], 0, 0); break;
					}
				}
				else if (spr_rotor2.getGlobalBounds().contains(translated_pos)) //increment the value of the rotor in position 2
				{
					
					switch (char_rotor2)
					{
					case 'A': char_rotor2 = 'B'; txt_rotor2.setString('B'); enigmaMachine.setRotors(current_rotors[1], 1, 1); break;
					case 'B': char_rotor2 = 'C'; txt_rotor2.setString('C'); enigmaMachine.setRotors(current_rotors[1], 2, 1); break;
					case 'C': char_rotor2 = 'D'; txt_rotor2.setString('D'); enigmaMachine.setRotors(current_rotors[1], 3, 1); break;
					case 'D': char_rotor2 = 'E'; txt_rotor2.setString('E'); enigmaMachine.setRotors(current_rotors[1], 4, 1); break;
					case 'E': char_rotor2 = 'F'; txt_rotor2.setString('F'); enigmaMachine.setRotors(current_rotors[1], 5, 1); break;
					case 'F': char_rotor2 = 'G'; txt_rotor2.setString('G'); enigmaMachine.setRotors(current_rotors[1], 6, 1); break;
					case 'G': char_rotor2 = 'H'; txt_rotor2.setString('H'); enigmaMachine.setRotors(current_rotors[1], 7, 1); break;
					case 'H': char_rotor2 = 'I'; txt_rotor2.setString('I'); enigmaMachine.setRotors(current_rotors[1], 8, 1); break;
					case 'I': char_rotor2 = 'J'; txt_rotor2.setString('J'); enigmaMachine.setRotors(current_rotors[1], 9, 1); break;
					case 'J': char_rotor2 = 'K'; txt_rotor2.setString('K'); enigmaMachine.setRotors(current_rotors[1], 10, 1); break;
					case 'K': char_rotor2 = 'L'; txt_rotor2.setString('L'); enigmaMachine.setRotors(current_rotors[1], 11, 1); break;
					case 'L': char_rotor2 = 'M'; txt_rotor2.setString('M'); enigmaMachine.setRotors(current_rotors[1], 12, 1); break;
					case 'M': char_rotor2 = 'N'; txt_rotor2.setString('N'); enigmaMachine.setRotors(current_rotors[1], 13, 1); break;
					case 'N': char_rotor2 = 'O'; txt_rotor2.setString('O'); enigmaMachine.setRotors(current_rotors[1], 14, 1); break;
					case 'O': char_rotor2 = 'P'; txt_rotor2.setString('P'); enigmaMachine.setRotors(current_rotors[1], 15, 1); break;
					case 'P': char_rotor2 = 'Q'; txt_rotor2.setString('Q'); enigmaMachine.setRotors(current_rotors[1], 16, 1); break;
					case 'Q': char_rotor2 = 'R'; txt_rotor2.setString('R'); enigmaMachine.setRotors(current_rotors[1], 17, 1); break;
					case 'R': char_rotor2 = 'S'; txt_rotor2.setString('S'); enigmaMachine.setRotors(current_rotors[1], 18, 1); break;
					case 'S': char_rotor2 = 'T'; txt_rotor2.setString('T'); enigmaMachine.setRotors(current_rotors[1], 19, 1); break;
					case 'T': char_rotor2 = 'U'; txt_rotor2.setString('U'); enigmaMachine.setRotors(current_rotors[1], 20, 1); break;
					case 'U': char_rotor2 = 'V'; txt_rotor2.setString('V'); enigmaMachine.setRotors(current_rotors[1], 21, 1); break;
					case 'V': char_rotor2 = 'W'; txt_rotor2.setString('W'); enigmaMachine.setRotors(current_rotors[1], 22, 1); break;
					case 'W': char_rotor2 = 'X'; txt_rotor2.setString('X'); enigmaMachine.setRotors(current_rotors[1], 23, 1); break;
					case 'X': char_rotor2 = 'Y'; txt_rotor2.setString('Y'); enigmaMachine.setRotors(current_rotors[1], 24, 1); break;
					case 'Y': char_rotor2 = 'Z'; txt_rotor2.setString('Z'); enigmaMachine.setRotors(current_rotors[1], 25, 1); break;
					case 'Z': char_rotor2 = 'A'; txt_rotor2.setString('A'); enigmaMachine.setRotors(current_rotors[1], 0, 1); break;
					}
				}
				else if (spr_rotor3.getGlobalBounds().contains(translated_pos)) //increment the value of the rotor in position 3
				{
					
					switch (char_rotor3)
					{
					case 'A': char_rotor3 = 'B'; txt_rotor3.setString('B'); enigmaMachine.setRotors(current_rotors[2], 1, 2); break;
					case 'B': char_rotor3 = 'C'; txt_rotor3.setString('C'); enigmaMachine.setRotors(current_rotors[2], 2, 2); break;
					case 'C': char_rotor3 = 'D'; txt_rotor3.setString('D'); enigmaMachine.setRotors(current_rotors[2], 3, 2); break;
					case 'D': char_rotor3 = 'E'; txt_rotor3.setString('E'); enigmaMachine.setRotors(current_rotors[2], 4, 2); break;
					case 'E': char_rotor3 = 'F'; txt_rotor3.setString('F'); enigmaMachine.setRotors(current_rotors[2], 5, 2); break;
					case 'F': char_rotor3 = 'G'; txt_rotor3.setString('G'); enigmaMachine.setRotors(current_rotors[2], 6, 2); break;
					case 'G': char_rotor3 = 'H'; txt_rotor3.setString('H'); enigmaMachine.setRotors(current_rotors[2], 7, 2); break;
					case 'H': char_rotor3 = 'I'; txt_rotor3.setString('I'); enigmaMachine.setRotors(current_rotors[2], 8, 2); break;
					case 'I': char_rotor3 = 'J'; txt_rotor3.setString('J'); enigmaMachine.setRotors(current_rotors[2], 9, 2); break;
					case 'J': char_rotor3 = 'K'; txt_rotor3.setString('K'); enigmaMachine.setRotors(current_rotors[2], 10, 2); break;
					case 'K': char_rotor3 = 'L'; txt_rotor3.setString('L'); enigmaMachine.setRotors(current_rotors[2], 11, 2); break;
					case 'L': char_rotor3 = 'M'; txt_rotor3.setString('M'); enigmaMachine.setRotors(current_rotors[2], 12, 2); break;
					case 'M': char_rotor3 = 'N'; txt_rotor3.setString('N'); enigmaMachine.setRotors(current_rotors[2], 13, 2); break;
					case 'N': char_rotor3 = 'O'; txt_rotor3.setString('O'); enigmaMachine.setRotors(current_rotors[2], 14, 2); break;
					case 'O': char_rotor3 = 'P'; txt_rotor3.setString('P'); enigmaMachine.setRotors(current_rotors[2], 15, 2); break;
					case 'P': char_rotor3 = 'Q'; txt_rotor3.setString('Q'); enigmaMachine.setRotors(current_rotors[2], 16, 2); break;
					case 'Q': char_rotor3 = 'R'; txt_rotor3.setString('R'); enigmaMachine.setRotors(current_rotors[2], 17, 2); break;
					case 'R': char_rotor3 = 'S'; txt_rotor3.setString('S'); enigmaMachine.setRotors(current_rotors[2], 18, 2); break;
					case 'S': char_rotor3 = 'T'; txt_rotor3.setString('T'); enigmaMachine.setRotors(current_rotors[2], 19, 2); break;
					case 'T': char_rotor3 = 'U'; txt_rotor3.setString('U'); enigmaMachine.setRotors(current_rotors[2], 20, 2); break;
					case 'U': char_rotor3 = 'V'; txt_rotor3.setString('V'); enigmaMachine.setRotors(current_rotors[2], 21, 2); break;
					case 'V': char_rotor3 = 'W'; txt_rotor3.setString('W'); enigmaMachine.setRotors(current_rotors[2], 22, 2); break;
					case 'W': char_rotor3 = 'X'; txt_rotor3.setString('X'); enigmaMachine.setRotors(current_rotors[2], 23, 2); break;
					case 'X': char_rotor3 = 'Y'; txt_rotor3.setString('Y'); enigmaMachine.setRotors(current_rotors[2], 24, 2); break;
					case 'Y': char_rotor3 = 'Z'; txt_rotor3.setString('Z'); enigmaMachine.setRotors(current_rotors[2], 25, 2); break;
					case 'Z': char_rotor3 = 'A'; txt_rotor3.setString('A'); enigmaMachine.setRotors(current_rotors[2], 0, 2); break;
					}
				}
				else if (spr_change_rotor1.getGlobalBounds().contains(translated_pos)) //if the user changes rotors in position 1, keep changing until a valid one is selected
				{
				    bool valid = false;
					while (!valid)
					{
						if (current_rotors[0] == 1 && current_rotors[1] != 2 && current_rotors[2] != 2)
						{
							current_rotors[0] = 2;
							valid = true;
						}
						else if (current_rotors[0] == 2 && current_rotors[1] != 3 && current_rotors[2] != 3)
						{
							current_rotors[0] = 3;
							valid = true;
						}
						else if (current_rotors[0] == 3 && current_rotors[1] != 4 && current_rotors[2] != 4)
						{
							current_rotors[0] = 4;
							valid = true;
						}
						else if (current_rotors[0] == 4 && current_rotors[1] != 5 && current_rotors[2] != 5)
						{
							current_rotors[0] = 5;
							valid = true;
						}
						else if (current_rotors[0] == 5 && current_rotors[1] != 1 && current_rotors[2] != 1)
						{
							current_rotors[0] = 1;
							valid = true;
						}
						if (!valid)
						{
							if (current_rotors[0] == 5)
							{
								current_rotors[0] = 1;
								
							}
							else
							{
								current_rotors[0]++;
							}
						}
					}
					switch (current_rotors[0]) //update text
					{
						case 1: txt_change_rotor1.setString("1"); enigmaMachine.setRotors(1, 0); break;
						case 2: txt_change_rotor1.setString("2"); enigmaMachine.setRotors(2, 0); break;
						case 3: txt_change_rotor1.setString("3"); enigmaMachine.setRotors(3, 0); break;
						case 4: txt_change_rotor1.setString("4"); enigmaMachine.setRotors(4, 0); break;
						case 5: txt_change_rotor1.setString("5"); enigmaMachine.setRotors(5, 0); break;
					}
                }
				else if (spr_change_rotor2.getGlobalBounds().contains(translated_pos)) //if the user changes rotors in position 2, keep changing until a valid one is selected
				{
				    bool valid = false;
				    while (!valid)
				    {
					    if (current_rotors[1] == 1 && current_rotors[2] != 2 && current_rotors[0] != 2)
						{
							current_rotors[1] = 2;
							valid = true;
						}
						else if (current_rotors[1] == 2 && current_rotors[2] != 3 && current_rotors[0] != 3)
						{
							current_rotors[1] = 3;
							valid = true;
						}
						else if (current_rotors[1] == 3 && current_rotors[2] != 4 && current_rotors[0] != 4)
						{
							current_rotors[1] = 4;
							valid = true;
						}
						else if (current_rotors[1] == 4 && current_rotors[2] != 5 && current_rotors[0] != 5)
						{
							current_rotors[1] = 5;
							valid = true;
						}
						else if (current_rotors[1] == 5 && current_rotors[2] != 1 && current_rotors[0] != 1)
						{
							current_rotors[1] = 1;
							valid = true;
						}
						if (!valid)
						{
							if (current_rotors[1] == 5)
							{
								current_rotors[1] = 1;
							
							}
							else
							{
								current_rotors[1]++;
							}
						
						}
					}
					switch (current_rotors[1]) //update text
					{
						case 1: txt_change_rotor2.setString("1"); enigmaMachine.setRotors(1, 1); break;
						case 2: txt_change_rotor2.setString("2"); enigmaMachine.setRotors(2, 1); break;
						case 3: txt_change_rotor2.setString("3"); enigmaMachine.setRotors(3, 1); break;
						case 4: txt_change_rotor2.setString("4"); enigmaMachine.setRotors(4, 1); break;
						case 5: txt_change_rotor2.setString("5"); enigmaMachine.setRotors(5, 1); break;
					}
			    }
				else if (spr_change_rotor3.getGlobalBounds().contains(translated_pos)) //if the user changes rotors in position 3, keep changing until a valid one is selected
				{
					bool valid = false;
					while (!valid)
					{
						if (current_rotors[2] == 1 && current_rotors[1] != 2 && current_rotors[0] != 2)
						{
							current_rotors[2] = 2;
							valid = true;
						}
						else if (current_rotors[2] == 2 && current_rotors[1] != 3 && current_rotors[0] != 3)
						{
							current_rotors[2] = 3;
							valid = true;
						}
						else if (current_rotors[2] == 3 && current_rotors[1] != 4 && current_rotors[0] != 4)
						{
							current_rotors[2] = 4;
							valid = true;
						}
						else if (current_rotors[2] == 4 && current_rotors[1] != 5 && current_rotors[0] != 5)
						{
							current_rotors[2] = 5;
							valid = true;
						}
						else if (current_rotors[2] == 5 && current_rotors[1] != 1 && current_rotors[0] != 1)
						{
							current_rotors[2] = 1;
							valid = true;
						}
						if (!valid)
						{
							if (current_rotors[2] == 5)
							{
								current_rotors[2] = 1;

							}
							else
							{
								current_rotors[2]++;
							}

						}
					}
					switch (current_rotors[2]) //update text
					{
						case 1: txt_change_rotor3.setString("1"); enigmaMachine.setRotors(1, 2); break;
						case 2: txt_change_rotor3.setString("2"); enigmaMachine.setRotors(2, 2); break;
						case 3: txt_change_rotor3.setString("3"); enigmaMachine.setRotors(3, 2); break;
						case 4: txt_change_rotor3.setString("4"); enigmaMachine.setRotors(4, 2); break;
						case 5: txt_change_rotor3.setString("5"); enigmaMachine.setRotors(5, 2); break;
					}
				}
				else if (spr_configure_plugs.getGlobalBounds().contains(translated_pos)) //user clicked to modify the plugboard
				{
					if (!setplug)
					{
						//set up the next two keypresses to modify the plugboard
						setplug = true;
						txt_enter_plug.setString("Enter the first letter on the plugboard to connect:");
					}
				}
				else if (spr_erase_plugs.getGlobalBounds().contains(translated_pos)) //reset the plugboards values and colours
				{
					for (int i = 0; i < 26; i++)
					{
						plugboard_sprite_vector[i].setColor(sf::Color(96, 96, 96));
					}
					enigmaMachine.resetPlugs();
				}
				
			}
			else if (event.type == sf::Event::TextEntered) //a keypressed was detected
			{
				if (!key_pressed) //if the key_release event hasn't been detected since the last keypress
				{
					
					if (find(begin(character_array), end(character_array), event.text.unicode) != end(character_array) && setplug == false) //if a valid key was pressed and plugboard values aren't being entered
					{
						while (user_input.getSize() > 31) //limit displayed text to 32 by erasing the oldest character if the current size exceeds 31
						{
							user_input.erase(0);
							//char_vector.erase(char_vector.begin());
						}
						current_key_pressed = event.key.code - 97;
						key_pressed = true; //dont accept new inputs until the key_release event has been triggered
						int input = 0;
						for (int i = 0; i < 26; i++) //determine what key was pressed
						{
							if (event.text.unicode == character_array[i])
							{
								input = i;
							}
						}
						int output = enigmaMachine.calculateOutput(input); //send the input character through the algorithm and return the output
						if (spacer < 4)
						{
							spacer++;
						}
						else //output a space every 5 characters
						{
							user_input += " ";
							spacer = 0;
						}
						user_input += character_array[output]; //add output to displayed text
						user_text.setString((user_input));
						bool rotate_rotor2 = false; //check if rotor in slot 2 needs rotated
						bool rotate_rotor3 = false; //check if rotor in slot 3 needs rotated
						sprite_vector[output].setColor(sf::Color(255, 255, 255)); //light up the sprite that corresponds to the output
						
						switch (char_rotor3) //rotate the rotor in slot 3, if it is in position Z then rotate the rotor in slot 2 as well
						{
						case 'A': char_rotor3 = 'B'; txt_rotor3.setString('B'); enigmaMachine.setRotors(current_rotors[2], 1, 2); break;
						case 'B': char_rotor3 = 'C'; txt_rotor3.setString('C'); enigmaMachine.setRotors(current_rotors[2], 2, 2); break;
						case 'C': char_rotor3 = 'D'; txt_rotor3.setString('D'); enigmaMachine.setRotors(current_rotors[2], 3, 2); break;
						case 'D': char_rotor3 = 'E'; txt_rotor3.setString('E'); enigmaMachine.setRotors(current_rotors[2], 4, 2); break;
						case 'E': char_rotor3 = 'F'; txt_rotor3.setString('F'); enigmaMachine.setRotors(current_rotors[2], 5, 2); break;
						case 'F': char_rotor3 = 'G'; txt_rotor3.setString('G'); enigmaMachine.setRotors(current_rotors[2], 6, 2); break;
						case 'G': char_rotor3 = 'H'; txt_rotor3.setString('H'); enigmaMachine.setRotors(current_rotors[2], 7, 2); break;
						case 'H': char_rotor3 = 'I'; txt_rotor3.setString('I'); enigmaMachine.setRotors(current_rotors[2], 8, 2); break;
						case 'I': char_rotor3 = 'J'; txt_rotor3.setString('J'); enigmaMachine.setRotors(current_rotors[2], 9, 2); break;
						case 'J': char_rotor3 = 'K'; txt_rotor3.setString('K'); enigmaMachine.setRotors(current_rotors[2], 10, 2); break;
						case 'K': char_rotor3 = 'L'; txt_rotor3.setString('L'); enigmaMachine.setRotors(current_rotors[2], 11, 2); break;
						case 'L': char_rotor3 = 'M'; txt_rotor3.setString('M'); enigmaMachine.setRotors(current_rotors[2], 12, 2); break;
						case 'M': char_rotor3 = 'N'; txt_rotor3.setString('N'); enigmaMachine.setRotors(current_rotors[2], 13, 2); break;
						case 'N': char_rotor3 = 'O'; txt_rotor3.setString('O'); enigmaMachine.setRotors(current_rotors[2], 14, 2); break;
						case 'O': char_rotor3 = 'P'; txt_rotor3.setString('P'); enigmaMachine.setRotors(current_rotors[2], 15, 2); break;
						case 'P': char_rotor3 = 'Q'; txt_rotor3.setString('Q'); enigmaMachine.setRotors(current_rotors[2], 16, 2); break;
						case 'Q': char_rotor3 = 'R'; txt_rotor3.setString('R'); enigmaMachine.setRotors(current_rotors[2], 17, 2); break;
						case 'R': char_rotor3 = 'S'; txt_rotor3.setString('S'); enigmaMachine.setRotors(current_rotors[2], 18, 2); break;
						case 'S': char_rotor3 = 'T'; txt_rotor3.setString('T'); enigmaMachine.setRotors(current_rotors[2], 19, 2); break;
						case 'T': char_rotor3 = 'U'; txt_rotor3.setString('U'); enigmaMachine.setRotors(current_rotors[2], 20, 2); break;
						case 'U': char_rotor3 = 'V'; txt_rotor3.setString('V'); enigmaMachine.setRotors(current_rotors[2], 21, 2); break;
						case 'V': char_rotor3 = 'W'; txt_rotor3.setString('W'); enigmaMachine.setRotors(current_rotors[2], 22, 2); break;
						case 'W': char_rotor3 = 'X'; txt_rotor3.setString('X'); enigmaMachine.setRotors(current_rotors[2], 23, 2); break;
						case 'X': char_rotor3 = 'Y'; txt_rotor3.setString('Y'); enigmaMachine.setRotors(current_rotors[2], 24, 2); break;
						case 'Y': char_rotor3 = 'Z'; txt_rotor3.setString('Z'); enigmaMachine.setRotors(current_rotors[2], 25, 2); break;
						case 'Z': char_rotor3 = 'A'; txt_rotor3.setString('A'); enigmaMachine.setRotors(current_rotors[2], 0, 2); rotate_rotor2 = true;  break;
						}
						
						if (rotate_rotor2)
						{
							
							switch (char_rotor2) //rotate the rotor in slot 2, if it is in position Z then rotate the rotor in slot 1 as well
							{
							case 'A': char_rotor2 = 'B'; txt_rotor2.setString('B'); enigmaMachine.setRotors(current_rotors[1], 1, 1); break;
							case 'B': char_rotor2 = 'C'; txt_rotor2.setString('C'); enigmaMachine.setRotors(current_rotors[1], 2, 1); break;
							case 'C': char_rotor2 = 'D'; txt_rotor2.setString('D'); enigmaMachine.setRotors(current_rotors[1], 3, 1); break;
							case 'D': char_rotor2 = 'E'; txt_rotor2.setString('E'); enigmaMachine.setRotors(current_rotors[1], 4, 1); break;
							case 'E': char_rotor2 = 'F'; txt_rotor2.setString('F'); enigmaMachine.setRotors(current_rotors[1], 5, 1); break;
							case 'F': char_rotor2 = 'G'; txt_rotor2.setString('G'); enigmaMachine.setRotors(current_rotors[1], 6, 1); break;
							case 'G': char_rotor2 = 'H'; txt_rotor2.setString('H'); enigmaMachine.setRotors(current_rotors[1], 7, 1); break;
							case 'H': char_rotor2 = 'I'; txt_rotor2.setString('I'); enigmaMachine.setRotors(current_rotors[1], 8, 1); break;
							case 'I': char_rotor2 = 'J'; txt_rotor2.setString('J'); enigmaMachine.setRotors(current_rotors[1], 9, 1); break;
							case 'J': char_rotor2 = 'K'; txt_rotor2.setString('K'); enigmaMachine.setRotors(current_rotors[1], 10, 1); break;
							case 'K': char_rotor2 = 'L'; txt_rotor2.setString('L'); enigmaMachine.setRotors(current_rotors[1], 11, 1); break;
							case 'L': char_rotor2 = 'M'; txt_rotor2.setString('M'); enigmaMachine.setRotors(current_rotors[1], 12, 1); break;
							case 'M': char_rotor2 = 'N'; txt_rotor2.setString('N'); enigmaMachine.setRotors(current_rotors[1], 13, 1); break;
							case 'N': char_rotor2 = 'O'; txt_rotor2.setString('O'); enigmaMachine.setRotors(current_rotors[1], 14, 1); break;
							case 'O': char_rotor2 = 'P'; txt_rotor2.setString('P'); enigmaMachine.setRotors(current_rotors[1], 15, 1); break;
							case 'P': char_rotor2 = 'Q'; txt_rotor2.setString('Q'); enigmaMachine.setRotors(current_rotors[1], 16, 1); break;
							case 'Q': char_rotor2 = 'R'; txt_rotor2.setString('R'); enigmaMachine.setRotors(current_rotors[1], 17, 1); break;
							case 'R': char_rotor2 = 'S'; txt_rotor2.setString('S'); enigmaMachine.setRotors(current_rotors[1], 18, 1); break;
							case 'S': char_rotor2 = 'T'; txt_rotor2.setString('T'); enigmaMachine.setRotors(current_rotors[1], 19, 1); break;
							case 'T': char_rotor2 = 'U'; txt_rotor2.setString('U'); enigmaMachine.setRotors(current_rotors[1], 20, 1); break;
							case 'U': char_rotor2 = 'V'; txt_rotor2.setString('V'); enigmaMachine.setRotors(current_rotors[1], 21, 1); break;
							case 'V': char_rotor2 = 'W'; txt_rotor2.setString('W'); enigmaMachine.setRotors(current_rotors[1], 22, 1); break;
							case 'W': char_rotor2 = 'X'; txt_rotor2.setString('X'); enigmaMachine.setRotors(current_rotors[1], 23, 1); break;
							case 'X': char_rotor2 = 'Y'; txt_rotor2.setString('Y'); enigmaMachine.setRotors(current_rotors[1], 24, 1); break;
							case 'Y': char_rotor2 = 'Z'; txt_rotor2.setString('Z'); enigmaMachine.setRotors(current_rotors[1], 25, 1); break;
							case 'Z': char_rotor2 = 'A'; txt_rotor2.setString('A'); enigmaMachine.setRotors(current_rotors[1], 0, 1); rotate_rotor3 = true; break;
							}
						}
						if (rotate_rotor3)
						{
							
							switch (char_rotor1) //rotate the rotor in slot 1
							{
							case 'A': char_rotor1 = 'B'; txt_rotor1.setString('B'); enigmaMachine.setRotors(current_rotors[0], 1, 0); break;
							case 'B': char_rotor1 = 'C'; txt_rotor1.setString('C'); enigmaMachine.setRotors(current_rotors[0], 2, 0); break;
							case 'C': char_rotor1 = 'D'; txt_rotor1.setString('D'); enigmaMachine.setRotors(current_rotors[0], 3, 0); break;
							case 'D': char_rotor1 = 'E'; txt_rotor1.setString('E'); enigmaMachine.setRotors(current_rotors[0], 4, 0); break;
							case 'E': char_rotor1 = 'F'; txt_rotor1.setString('F'); enigmaMachine.setRotors(current_rotors[0], 5, 0); break;
							case 'F': char_rotor1 = 'G'; txt_rotor1.setString('G'); enigmaMachine.setRotors(current_rotors[0], 6, 0); break;
							case 'G': char_rotor1 = 'H'; txt_rotor1.setString('H'); enigmaMachine.setRotors(current_rotors[0], 7, 0); break;
							case 'H': char_rotor1 = 'I'; txt_rotor1.setString('I'); enigmaMachine.setRotors(current_rotors[0], 8, 0); break;
							case 'I': char_rotor1 = 'J'; txt_rotor1.setString('J'); enigmaMachine.setRotors(current_rotors[0], 9, 0); break;
							case 'J': char_rotor1 = 'K'; txt_rotor1.setString('K'); enigmaMachine.setRotors(current_rotors[0], 10, 0); break;
							case 'K': char_rotor1 = 'L'; txt_rotor1.setString('L'); enigmaMachine.setRotors(current_rotors[0], 11, 0); break;
							case 'L': char_rotor1 = 'M'; txt_rotor1.setString('M'); enigmaMachine.setRotors(current_rotors[0], 12, 0); break;
							case 'M': char_rotor1 = 'N'; txt_rotor1.setString('N'); enigmaMachine.setRotors(current_rotors[0], 13, 0); break;
							case 'N': char_rotor1 = 'O'; txt_rotor1.setString('O'); enigmaMachine.setRotors(current_rotors[0], 14, 0); break;
							case 'O': char_rotor1 = 'P'; txt_rotor1.setString('P'); enigmaMachine.setRotors(current_rotors[0], 15, 0); break;
							case 'P': char_rotor1 = 'Q'; txt_rotor1.setString('Q'); enigmaMachine.setRotors(current_rotors[0], 16, 0); break;
							case 'Q': char_rotor1 = 'R'; txt_rotor1.setString('R'); enigmaMachine.setRotors(current_rotors[0], 17, 0); break;
							case 'R': char_rotor1 = 'S'; txt_rotor1.setString('S'); enigmaMachine.setRotors(current_rotors[0], 18, 0); break;
							case 'S': char_rotor1 = 'T'; txt_rotor1.setString('T'); enigmaMachine.setRotors(current_rotors[0], 19, 0); break;
							case 'T': char_rotor1 = 'U'; txt_rotor1.setString('U'); enigmaMachine.setRotors(current_rotors[0], 20, 0); break;
							case 'U': char_rotor1 = 'V'; txt_rotor1.setString('V'); enigmaMachine.setRotors(current_rotors[0], 21, 0); break;
							case 'V': char_rotor1 = 'W'; txt_rotor1.setString('W'); enigmaMachine.setRotors(current_rotors[0], 22, 0); break;
							case 'W': char_rotor1 = 'X'; txt_rotor1.setString('X'); enigmaMachine.setRotors(current_rotors[0], 23, 0); break;
							case 'X': char_rotor1 = 'Y'; txt_rotor1.setString('Y'); enigmaMachine.setRotors(current_rotors[0], 24, 0); break;
							case 'Y': char_rotor1 = 'Z'; txt_rotor1.setString('Z'); enigmaMachine.setRotors(current_rotors[0], 25, 0); break;
							case 'Z': char_rotor1 = 'A'; txt_rotor1.setString('A'); enigmaMachine.setRotors(current_rotors[0], 0, 0); break;
							}
						}
						rotate_rotor2 = false; //reset these values to false so they dont keep rotating
						rotate_rotor3 = false;
					}
					else if (find(begin(character_array), end(character_array), event.text.unicode) != end(character_array) && setplug == true && firstPlugEntered == false) //valid keypress, first character is being input for plugboard
					{
						firstplug = event.text.unicode;
						firstPlugEntered = true;
						txt_enter_plug.setString("Enter the second letter on the plugboard to connect:");
					}
					else if (find(begin(character_array), end(character_array), event.text.unicode) != end(character_array) && setplug == true && firstPlugEntered == true) //valid keypress, second character is being input for plugboard
					{
						secondplug = event.text.unicode;
						setplug = false;
						firstPlugEntered = false;
						txt_enter_plug.setString("");
						int spriteOne = 0;
						int spriteTwo = 0;
						switch (firstplug) //select sprites based on the two characters entered
						{
						    case 'a': spriteOne = 0; break;
							case 'b': spriteOne = 1; break;
							case 'c': spriteOne = 2; break;
							case 'd': spriteOne = 3; break;
							case 'e': spriteOne = 4; break;
							case 'f': spriteOne = 5; break;
							case 'g': spriteOne = 6; break;
							case 'h': spriteOne = 7; break;
							case 'i': spriteOne = 8; break;
							case 'j': spriteOne = 9; break;
							case 'k': spriteOne = 10; break;
							case 'l': spriteOne = 11; break;
							case 'm': spriteOne = 12; break;
							case 'n': spriteOne = 13; break;
							case 'o': spriteOne = 14; break;
							case 'p': spriteOne = 15; break;
							case 'q': spriteOne = 16; break;
							case 'r': spriteOne = 17; break;
							case 's': spriteOne = 18; break;
							case 't': spriteOne = 19; break;
							case 'u': spriteOne = 20; break;
							case 'v': spriteOne = 21; break;
							case 'w': spriteOne = 22; break;
							case 'x': spriteOne = 23; break;
							case 'y': spriteOne = 24; break;
							case 'z': spriteOne = 25; break;
							
						}
						switch (secondplug)
						{
						case 'a': spriteTwo = 0; break;
						case 'b': spriteTwo = 1; break;
						case 'c': spriteTwo = 2; break;
						case 'd': spriteTwo = 3; break;
						case 'e': spriteTwo = 4; break;
						case 'f': spriteTwo = 5; break;
						case 'g': spriteTwo = 6; break;
						case 'h': spriteTwo = 7; break;
						case 'i': spriteTwo = 8; break;
						case 'j': spriteTwo = 9; break;
						case 'k': spriteTwo = 10; break;
						case 'l': spriteTwo = 11; break;
						case 'm': spriteTwo = 12; break;
						case 'n': spriteTwo = 13; break;
						case 'o': spriteTwo = 14; break;
						case 'p': spriteTwo = 15; break;
						case 'q': spriteTwo = 16; break;
						case 'r': spriteTwo = 17; break;
						case 's': spriteTwo = 18; break;
						case 't': spriteTwo = 19; break;
						case 'u': spriteTwo = 20; break;
						case 'v': spriteTwo = 21; break;
						case 'w': spriteTwo = 22; break;
						case 'x': spriteTwo = 23; break;
						case 'y': spriteTwo = 24; break;
						case 'z': spriteTwo = 25; break;

						}
						if(enigmaMachine.getPlugValue(spriteOne) == -1 && enigmaMachine.getPlugValue(spriteTwo) == -1 && spriteOne != spriteTwo) //if the entered plugs aren't already lit up, light them up with matching colours
						{
							enigmaMachine.setPlugValue(spriteOne, spriteTwo);
							plugboard_sprite_vector[spriteOne].setColor(colour_vector[colour_counter]);
							plugboard_sprite_vector[spriteTwo].setColor(colour_vector[colour_counter]);
							colour_counter++;
							if (colour_counter == 13) //reset colour vector if it has reached the end
							{
								colour_counter = 0;
							}
						}
						
					}
				}
			}
			else if (event.type == sf::Event::KeyReleased) //user has released a key
			{
				if (event.key.code == current_key_pressed) //if the release key is the one that was originally pressed
				{
					key_pressed = false; //record that the key was released
					for (int i = 0; i < sprite_vector.size(); i++) //reset sprites to original colour
					{
						sprite_vector[i].setColor(sf::Color(128, 128, 128));
					}
				}
			}
		}

		//DRAW SPRITES TO THE WINDOW AND DISPLAY

		spr_typebox1.setPosition(130, 100);
		spr_typebox3.setPosition(920, 100);
		for (int i = 130; i < 920; i += 40)
		{
			spr_typebox2.setPosition(i, 100);
			window.draw(spr_typebox2);
		}
		window.draw(spr_rotor1);
		window.draw(spr_change_rotor1);
		window.draw(spr_rotor2);
		window.draw(spr_change_rotor2);
		window.draw(spr_rotor3);
		window.draw(spr_change_rotor3);
		window.draw(spr_typebox1);
		window.draw(spr_typebox3);
		window.draw(spr_configure_plugs);
		window.draw(spr_erase_plugs);
		window.draw(spr_erase);
		window.draw(txt_erase);
		window.draw(encrpyted_text);
		window.draw(title_string);
		window.draw(subtitle_string1);
		window.draw(subtitle_string2);
		window.draw(subtitle_string3);
		window.draw(txt_rotor1);
		window.draw(txt_rotor2);
		window.draw(txt_rotor3);
		window.draw(txt_change_rotor1);
		window.draw(txt_change_rotor2);
		window.draw(txt_change_rotor3);
		window.draw(txt_configure_plugs);
		window.draw(txt_enter_plug);
		window.draw(txt_erase_text);
		window.draw(user_text);
		
		for (int i = 0; i < sprite_vector.size(); i++)
		{
			window.draw(sprite_vector[i]);
		}
		for (int i = 0; i < plugboard_sprite_vector.size(); i++)
		{
			window.draw(plugboard_sprite_vector[i]);
		}
		window.display();
	}
}