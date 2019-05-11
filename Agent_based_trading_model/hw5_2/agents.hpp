//
//  agents.hpp
//  hw5_2
//
//  Created by Jonathan Kaplan on 3/6/19.
//  Copyright © 2019 Jonathan Kaplan. All rights reserved.
//

#include <string>
#include <vector>
#include "dealer.hpp"


using namespace std;

#ifndef agents_hpp
#define agents_hpp

class Dealer; // we need to let the compiler know that Dealer is a class

class Agent {
public:
    double tradeProb;
    double tradeScale;
    // starting values
    double startingCash;
    double startingShares;
    // current values
    double cash;
    double shares;
public:
    Agent(double tradeProb, double tradeScale, double cash, double shares);
    //virtual ~Agent();
    virtual void tick(double net, Dealer* dealer)=0;
    double getNAV(double price);
    virtual void reset();
    void adjustHoldings(double cash, double shares);
};


class ValueAgent:public Agent{
public:
    ValueAgent(double tradeProb,
               double tradeScale,
               double cash,
               double shares) :
    Agent(tradeProb, tradeScale, cash, shares) {}
    void tick(double net, Dealer* dealer);
    //~ValueAgent();
    
};

class MomentumAgent:public Agent {
public:
    double prevNet;
    MomentumAgent(double tradeProb,
                  double tradeScale,
                  double cash,
                  double shares) :
    Agent(tradeProb, tradeScale, cash, shares), prevNet(0) {}
    void tick(double net, Dealer* dealer);
    void reset();
    //~MomentumAgent();
};

class NoiseAgent:public Agent {
public:
    NoiseAgent(double tradeScale) :
    Agent(1.0, tradeScale, 0, 0) {}
    void tick(double net, Dealer* dealer);
    //~NoiseAgent();
};

#endif /* agents_hpp */


