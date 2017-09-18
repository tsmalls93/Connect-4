#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Ball {
public:
    int val;
    int matched;
    Ball *low;
    Ball *high;
};


class OneDimensionalBalls {
public:
    long long countValidGuesses(vector <int> firstPicture, vector <int> secondPicture);
    long long cvg(int v);
    void ptrAssign(int v);
    void FPNulls(int v);
    void SPNulls();
    long long guessCount(int v);
    bool noValids();
    int simpleChain();
    map <int, Ball*> FP;
    map <int, Ball*> SP;
};


int OneDimensionalBalls::simpleChain(){
    //look for balls in FP with only one valid pointer
    for (map<int,Ball*>::iterator it = FP.begin(); it!=FP.end(); it++){
        if (it->second->low == NULL and it->second->high != NULL and it->second->matched == 0){
            //this ball has been matched
            it->second->matched = 1;
            //same for the one it is matched to
            it->second->high->matched = 1;
            //does that ball have another valid pointer?
            if (it->second->high->high != NULL){
                it->second->high->high->matched = 1;
                it->second->high->high->low = NULL;
                it->second->high->high = NULL;
                
            }
            //remove links
            it->second->high->low = NULL;
            it->second->high = NULL;
            delete it->second->high;
        } else if (it->second->low != NULL and it->second->high == NULL and it->second->matched == 0){
            //same as above
            it->second->matched = 1;
            it->second->low->matched = 1;
            if (it->second->low->low != NULL){
                it->second->low->low->matched = 1;
                it->second->low->low->high = NULL;
                it->second->low->low = NULL;
            }
            it->second->low->high = NULL;
            it->second->low = NULL;
            delete it->second->low;
        } else if (it->second->low == NULL and it->second->high == NULL and it->second->matched == 0)
            return 0;
    }
    //look for ball SP with only one pointer
    for (map<int,Ball*>::iterator it = SP.begin(); it!=SP.end(); it++){
        if (it->second->low == NULL and it->second->high != NULL and it->second->matched == 1){
            it->second->high->matched = 1;
            it->second->high->low->matched = 1;
            if (it->second->high->high != NULL){
                it->second->high->high->matched = 1;
                it->second->high->high->low = NULL;
                it->second->high->high = NULL;
            }
            it->second->high->low = NULL;
            it->second->high = NULL;
            delete it->second->high;
        } else if (it->second->low != NULL and it->second->high == NULL and it->second->matched == 1){
            it->second->low->matched = 1;
            it->second->low->high->matched = 1;
            if (it->second->low->low != NULL){
                it->second->low->low->matched = 1;
                it->second->low->low->high = NULL;
                it->second->low->low = NULL;
            }
            it->second->low->high = NULL;
            it->second->low = NULL;
        }
    }
    
    //are all of the balls in FP matched?
    bool flag = true;
    for (map<int,Ball*>::iterator it = FP.begin(); it!=FP.end(); it++){
        if (it->second->matched != 1){
            flag = false;
        }
    }
    if (flag){
        return 1;
    } else {
        return -1;
    }
}

//is there no valid guess?
bool OneDimensionalBalls::noValids(){
    //does any ball in FP have no pointers
    for (map<int,Ball*>::iterator it = FP.begin(); it!=FP.end(); it++){
        if (it->second->low == NULL and it->second->high == NULL and it->second->matched == 0){
            return true;
        }
    }
    return false;
}


long long OneDimensionalBalls::guessCount(int v){
    long long ct;
    long long rv = 1;
    bool flag = false;
    for (map<int, Ball*>::iterator it=FP.begin(); it!=FP.end();){
        if (it->second->matched == 0 and it->second->low->low ==NULL and it->second->low!=NULL and it->second->high != NULL){
            flag = true;
            //begin count
            ct = 0;
            Ball* b = it->second;
            while(b->high!=NULL and b->matched == 0){
                ct++;
                b->matched = 1;
                if(b->high==NULL)
                    break;
                b->low = NULL;
                b = b->high;
            }
            ct/=2;
            ct+=2;
            rv*=ct;
            SPNulls();
            it = FP.begin();
        } else {
            it++;
        }
    }
    
    return rv;
}



//deletes anything in SP with both pointers NULL
void OneDimensionalBalls::SPNulls(){
    for (;;){
        for (map<int, Ball*>::iterator it2=SP.begin(); it2!=SP.end(); it2++){
            //both null?
            if ((it2->second->high == NULL and it2->second->low == NULL) or it2->second->matched == 1){
                delete it2->second;
                SP.erase(it2);
                break;
            }
        }
        //any nulls left? if not break out.
        int ct = 0;
        for (map<int, Ball*>::iterator it2=SP.begin(); it2!=SP.end(); it2++)
        {
            //null found
            if((it2->second->low == NULL and it2->second->high == NULL) or it2->second->matched == 1)
                ct++;
            else
                continue;
        }
        //no more nulls
        if (ct==0)
            break;
    }
    
}

//deletes anything in FP with a matched pointer
void OneDimensionalBalls::FPNulls(int v){
    //Find null pointers in FP, delete ball and corresponding non-null pointer
    //forever loop break out if no more nulls
    for(;;){
        for(map<int,Ball*>::iterator it=FP.begin(); it!=FP.end(); it++)
        {
            //case matched
            if (it->second->matched == 1){
                delete it->second;
                FP.erase(it);
            }
            //case one null
            if(it->second->low == NULL or it->second->high == NULL)
            {
                //case low null
                if(it->second->low == NULL)
                {
                    //remove ball FP[i] and remove corresponding high ball in SP
                    for (map<int,Ball*>::iterator it2=SP.begin(); it2!=SP.end(); it2++){
                        if (it2->first == (it->first)+v){
                            delete it2->second;
                            SP.erase(it2);
                            break;
                        }
                    }
                    delete it->second;
                    FP.erase(it);
                    break;
                }
                //case high null
                if (it->second->high == NULL)
                {
                    //remove ball FP[i] and remove corresponding low ball in SP
                    for (map<int, Ball*>::iterator it2=SP.begin(); it2!=SP.end(); it2++){
                        if (it2->first == it->first-v){
                            delete it2->second;
                            SP.erase(it2);
                            break;
                        }
                    }
                    delete it->second;
                    FP.erase(it);
                    break;
                }
            }
        }
        //any nulls left? if not break out.
        int ct = 0;
        for (map<int,Ball*>::iterator it=FP.begin(); it!=FP.end(); it++)
        {
            if(it->second->low == NULL or it->second->high == NULL)
                ct++;
            else
                continue;
        }
        if (ct==0)
            break;
    }
}

//assign pointers
void OneDimensionalBalls::ptrAssign(int v){
    //assign pointers for balls in FP
    for (map<int, Ball*>::iterator it=FP.begin(); it!=FP.end(); it++)
    {
        //look through SP to see if there is a ball with value of (*it)->val+v
        //then assign (*it)->high to said ball in SP otherwise do nothing as it is already null
        for(map<int, Ball*>::iterator it2=SP.begin(); it2!=SP.end(); it2++){
            if(it2->first==it->first+v){
                it->second->high = it2->second;
            }
        }
        //look through SP to see if there is a ball with value of (*it)->val-v
        //then assign (*it)->low to said ball in SP otherwise do nothing as it is already null
        for(map<int, Ball*>::iterator it2=SP.begin(); it2!=SP.end(); it2++){
            if(it2->first==it->first-v){
                it->second->low = it2->second;
            }
        }
        
    }
    //assign pointers for balls in SP
    for (map<int, Ball*>::iterator it=SP.begin(); it!=SP.end(); it++){
        //look through FP to see if there is a ball with a value of (*it)->val-v
        //assign both high and low to said ball
        for(map<int, Ball*>::iterator it2=FP.begin(); it2!=FP.end(); it2++){
            if(it2->first==it->first-v){
                it->second->low = it2->second;
            }
        }
        for(map<int, Ball*>::iterator it2=FP.begin(); it2!=FP.end(); it2++){
            if(it2->first==it->first+v){
                it->second->high = it2->second;
            }
        }
    }
    
}


long long OneDimensionalBalls::cvg(int v)
{
    //assign pointers
    ptrAssign(v);
    //check if any ball in FP has no pointers
    if (noValids() == true)
        return 0;
    if (simpleChain() == 1)
        return 1;
    else if (simpleChain() == 0)
        return 0;
    if (noValids() == true)
        return 0;
    SPNulls();
    //calculate the guesses from the complex chains
    return guessCount(v);
}

//sums the valid guesses from cvg, sets up pointers
long long OneDimensionalBalls::countValidGuesses(vector <int> firstPicture, vector <int> secondPicture)
{
    int i, d;
    set <int> velocities;
    set <int>::iterator vit;
    long long rv;
    
    for (i = 0; i < secondPicture.size(); i++) {
        d = secondPicture[i] - firstPicture[0];
        if (d < 0) d = -d;
        if (d != 0) velocities.insert(d);
    }
    //if time has passed and the same number of balls are in each picture
    if (velocities.size() > 1 and firstPicture.size() == secondPicture.size()){
        return 0;
    }
    rv = 0;
    for (vit = velocities.begin(); vit != velocities.end(); vit++) {
        FP.clear();
        SP.clear();
        for (int i=0; i<firstPicture.size(); i++){
            Ball* b = new Ball();
            b->val = firstPicture[i];
            b->matched = 0;
            b->high = NULL;
            b->low = NULL;
            FP.insert(make_pair(b->val,b));
        }
        for (int i=0; i<secondPicture.size(); i++){
            Ball* b = new Ball();
            b->val = secondPicture[i];
            b->matched = 0;
            b->high = NULL;
            b->low = NULL;
            SP.insert(make_pair(b->val, b));
        }
        rv += cvg(*vit);
    }
    return rv;
}
