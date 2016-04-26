#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>		// list
#include <set>		// set
#include <iostream>     // cout
#include <functional>   // greater
#include <algorithm>    // sort
#include <queue> 	// queue

using namespace std;
////////////////// Exercise 1 ////////////////////////////////////
float calc_mean(const list<float> values) {
	// Initialize variable	
	float sum = 0.f;

	// Loop through the list to get the sum
	for (list<float>::const_iterator it = values.begin(); it != values.end(); it++) {
		sum += *it;
	}

	// Calculate the mean by dividing the sum by the size of the list
	float mean = sum / values.size();

	// Return it afterwards
	return mean;
}

float calc_StandardDeviation(const list<float> values, float mean) {
	// Initialize variable
	float cum_dev = 0.f;

	// Loop through the list
	for (list<float>::const_iterator it = values.begin(); it != values.end(); it++) {
		// To get the square of the difference of the value and the mean
		cum_dev += pow((mean - *it), 2);
	}

	// Calculate the mean of it
	cum_dev = cum_dev / values.size();

	// And then take the square root of it
	cum_dev = sqrt(cum_dev);

	// Return it as last
	return cum_dev;
}


pair<float, float> Statistics(const list<float>& values)
{
	// If the values list is empty, return 0
	if (values.size() == 0) return pair<float, float>(0.f, 0.f);
	
	// Otherwise calculate the mean
	float mean = calc_mean(values);
	// And calculate the standard deviation
	float standard_Deviation = calc_StandardDeviation(values, mean);
	
	// And return it
	return pair<float, float>(mean, standard_Deviation);
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 2 ////////////////////////////////////
class TreeVisitor {
public:
	float visitTree(const Tree& tree, bool countOnlyEvenLevels) {
		float count = 0.f;
		return visitTree_recursive(tree, countOnlyEvenLevels, count);
	}

	float visitTree_recursive(const Tree& tree, bool countOnlyEvenLevels, float &count) {
		list<Tree>::const_iterator iterator;
		list<Tree> children = tree.children;
		Tree temp;

		for (iterator = children.begin(); iterator != children.end(); ++iterator) {
			temp = *iterator;
			if (countOnlyEvenLevels == true && ((int)(temp.value / 2) % 2) != 0) {
				visitTree_recursive(temp, countOnlyEvenLevels, count);
			}
			else {
				count += temp.value;
				visitTree_recursive(temp, countOnlyEvenLevels, count);
			}
		}
		return count;
	}
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex {

	friend
		Complex operator +(const Complex & a, const Complex & b) {
		return Complex((a.real + b.real), (a.im + b.im));
	}

	friend
		Complex operator -(const Complex & a, const Complex & b) {
		return Complex((a.real - b.real), (a.im - b.im));
	}

	friend
		Complex operator *(const Complex & a, const Complex & b) {
		return Complex(((a.real * b.real) - (a.im * b.im)), ((a.im * b.real) + (a.real*b.im)));
	}

	public:
		
		Complex(float m_real, float m_imaginary) {
			real = m_real;
			im = m_imaginary;

		}

		float real, im;
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(list<float> heights) {
    vector<float> listHeights(heights.begin(), heights.end());
    float volume = 0.0f;
    unsigned int startx = 0;
    unsigned int startheight = 0;
    unsigned int endx = 0;
    unsigned int endheight = 0;
    unsigned int heights_total = listHeights.size();
    vector<float> steps;
    float stepsvolume = 0.0f;

    for(unsigned int x=0; x<heights_total; x++) {
        if(x+1 < heights_total && listHeights[x] > listHeights[x+1] ) {
            startx = x;
            startheight = listHeights[startx];
            break;
        }
    }

    //not end
    bool bEnd = false;
    for(unsigned int x=0; x<heights_total; x++) {
        if(x+1 <= heights_total && listHeights[x] > listHeights[x+1]) {
            bEnd = true;
        } else {
            bEnd = false;
            break;
        }
    }

    if(bEnd == true) return 0.0f;

    heights_total = heights_total - startx;
    bool found = false;
    for(unsigned int x=startx+1; x<heights_total; x++) {
        if(listHeights[x] >= startheight) {
            endx = x;
            endheight = listHeights[x];
            found = true;
            break;
        } else {
            steps.push_back(listHeights[x]);
            stepsvolume += listHeights[x];
        }
    }

    if(found == false) {
        steps.clear();
        stepsvolume = 0;
        for(unsigned int x=startx+1; x<heights_total; x++) {
            if(listHeights[x] >= endheight) {
                endx = x;
                endheight = listHeights[x];
                found = true;
            }
        }
    }

    if(startheight > endheight) {
        for(unsigned int x=startx+1; x<endx; x++) {
            stepsvolume += listHeights[x];
            steps.push_back(listHeights[x]);
        }
        volume += endheight * steps.size() - stepsvolume;
    }

    if(startheight <= endheight) {
        volume += startheight * steps.size() - stepsvolume;
    }

    std:list<float> newList;
    for(unsigned int i = endx; i<listHeights.size(); i++) {
        newList.push_back(listHeights[i]);
    }

    return volume + WaterLevels(newList);
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
typedef std::pair<int, int> location;

int Labyrinth(set<pair<location, location> > labyrinth, int size)
{
	set<location> visited;
	queue<location> q;
	int pathlength = 0;
	q.push(location(0,0));

	while(!q.empty()) {
		location current = q.front();
		q.pop();
		visited.insert(current);

		if (current == location(size-1, size-1)) {
			return pathlength;
		}

		set<location> newLocations;
		newLocations.insert(location(current.first+1, current.second));
		newLocations.insert(location(current.first-1, current.second));
		newLocations.insert(location(current.first, current.second+1));
		newLocations.insert(location(current.first, current.second-1));

		bool newLocation = false;

		for (set<location>::iterator it = newLocations.begin(); it != newLocations.end(); ++it) {
			if (it->first < 0 || it->first>size-1 || it->second<0 || it->second>size-1 || (visited.find(*it) != visited.end() ) ) {
				if (!(labyrinth.find(pair<location, location>(current, *it)) != labyrinth.end()) || (labyrinth.find(pair<location, location>(*it, current)) != labyrinth.end()) ) {
					q.push(*it);
					newLocation = true;
				}
			}
		}

		if (newLocation) {
			pathlength++;
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////////////

#endif
