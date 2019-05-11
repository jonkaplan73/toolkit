//
//  agents.cpp
//  hw5_2
//
//  Created by Jonathan Kaplan on 3/6/19.
//  Copyright © 2019 Jonathan Kaplan. All rights reserved.
//

#include "agents.hpp"
#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <ctime>
#include <cmath>


using namespace std;


Agent::Agent(double tradeProb, double tradeScale, double cash, double shares):tradeProb(tradeProb),tradeScale(tradeScale),cash(cash),shares(shares){}


void Agent::reset(){
    cash = startingCash;
    shares = startingShares;
}

double Agent::getNAV(double price){
    return cash  + shares * price;
};


void Agent::adjustHoldings(double cash, double shares){
    this->cash =  this->cash + cash;
    this->shares  = this->shares + shares;
}

void ValueAgent::tick(double net, Dealer* dealer){
    double percentageToTrade = (-1/2)+(1/(1+exp(tradeScale*net)));
    if (percentageToTrade > 0.0){
        shares = dealer->buyShares(percentageToTrade * cash);
        adjustHoldings(-percentageToTrade * cash, shares);
    } else {
        double dollars = dealer->sellShares(-percentageToTrade * shares);
        adjustHoldings(dollars, percentageToTrade * shares);
    }
}

void MomentumAgent::tick(double net, Dealer* dealer) {
    double netDelta = net - prevNet;
    // update previously observed net
    prevNet = net;
    double percentageToTrade = (-1/2)+(1/(1+exp(-tradeScale*netDelta)));
    if (percentageToTrade > 0.0){
        shares = dealer->buyShares(percentageToTrade * cash);
        adjustHoldings(-percentageToTrade * cash, shares);
    } else {
        double dollars = dealer->sellShares(-percentageToTrade * shares);
        adjustHoldings(dollars, percentageToTrade * shares);
    }
}

void MomentumAgent::reset(){
    Agent::reset();
    prevNet = 0;
}

void NoiseAgent::tick(double net, Dealer* dealer){
    std::default_random_engine generator;
    std::mt19937 mt_rand(time(0));
    std::normal_distribution<double> dis_norm(0,1);
    double dollars = dis_norm(mt_rand) * tradeScale;
    if (dollars > 0) {
        dealer->buyShares(dollars);
    } else {
        dealer->sellShares(-dollars / dealer->getPrice());
    }
}
