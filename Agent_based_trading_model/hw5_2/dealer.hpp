//
//  dealer.hpp
//  hw5_2
//
//  Created by Jonathan Kaplan on 3/6/19.
//  Copyright © 2019 Jonathan Kaplan. All rights reserved.
//

#ifndef dealer_hpp
#define dealer_hpp

#include <stdio.h>
#include "agents.hpp"

class Dealer {
public:
    vector<Agent*> agents;
    double net;
    double priceScale;
private:
    double periodNet;
public:
    Dealer(double priceScale);
    virtual ~Dealer();
    void addAgent(const string& agentType,double tradeProb,double tradeScale,double cash,double shares);
    void runSimulation(int numSimulations, int numPeriods,vector<vector<double>> & simResults);
    double buyShares(double dollars);
    double sellShares(double shares);
    double getPrice();
};

#endif /* dealer_hpp */
