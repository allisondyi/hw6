#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
    // Add your code here
    //last 6 letters first
    unsigned long long w[5]= {0};
    int size=k.size()-1; //i 
    int factor=1; //factor 
    int counter=0;
    while (size>=0 and counter<6) { //starting backwards  //dunno if counter<5 
			//std::cout<<"size"<<size<<std::endl;
			char temp= tolower(k[size]);
			w[4]+=factor*letterDigitToNumber(temp);
			//std::cout<<w[4]<<std::endl;
			factor=factor*36;
			counter++;
			size--;
    }
    int group=3;
    while (size>=0) {
			int x=1;
			for (int y=5; y>=0;y--) {
				if (size<0) {
					break;
				}
				char temp=tolower(k[size]);
				w[group]+=x*letterDigitToNumber(temp);
				x=x*36;
				size--;
			}
			group--;
			//std::cout<<"we are adding one to group"<<group<<std::endl;
			//std::cout<<"size"<<size<<std::endl;
    }
    // unsigned long long r[5];
    // r[0]=983132572;
    // r[1]=1468777056;
    // r[2]=552714139; 
    // r[3]=984953261; 
    // r[4]=261934300;
    unsigned long long hash=0;
    for (int z=0; z<5;z++) {
		//	std::cout<<"this is r["<<z<<"] "<<r[z]<<std::endl;
			//std::cout<<"this is w["<<z<<"] "<<w[z]<<std::endl;
      hash+=rValues[z]*w[z];
			//std::cout<<"this is hash "<<hash<<std::endl;
    }
    return hash;
}

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
		// Add code here or delete this helper function if you do not want it
		if (isdigit(letter)) { //it is a number
			//std::cout<<"this is the number "<<letter<<" "<<letter-'0'+26<<std::endl;
			return letter-'0'+26;
		}
		else if (isalpha(letter)) { //is alphabet
			//std::cout<<"this is the letter "<<letter<<tolower(letter)-'a'<<std::endl;
			return tolower(letter)-'a';
		}
		else { //is not alphanumeric
			return 0; 
		}
  }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif


