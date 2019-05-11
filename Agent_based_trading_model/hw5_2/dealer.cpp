//
//  dealer.cpp
//  hw5_2
//
//  Created by Jonathan Kaplan on 3/6/19.
//  Copyright © 2019 Jonathan Kaplan. All rights reserved.
//

#include "dealer.hpp"
#include "agents.hpp"
#include <random>

Dealer::Dealer(double priceScale):priceScale(priceScale),net(0){}

Dealer::~Dealer()
{
    //Agent::~Agent();
    agents.clear();
    //delete[] agents;
    //agents = std::vector<Agent*>
}

void Dealer::addAgent(const string& agentType,double tradeProb,double tradeScale,double cash,double shares){
    if(agentType == "value"){
        agents.push_back(new ValueAgent(tradeProb,tradeScale, cash,shares));
    }
    if(agentType == "momentum"){
        agents.push_back(new MomentumAgent(tradeProb,tradeScale, cash,shares));
    }
    if(agentType == "noise"){
        agents.push_back(new NoiseAgent(tradeScale));
    }
}



void Dealer::runSimulation(int numSimulations, int numPeriods,vector<vector<double>> & simResults) {
    simResults.clear();
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> unif(0, 1);
    for(int i =0; i < numSimulations; i++){
        vector<double> priceHistory;
        //Dealer::~Dealer();
        //Reset all agents - done in agent loop
        net = 0;
        for(int n =0; n < numPeriods; n++){
            periodNet = 0;
            for(int agent_id =0; agent_id < agents.size(); agent_id++){
                agents[agent_id]->reset();
                double u = unif(rng);
                if (u < agents[agent_id]->tradeProb) { //agents[agent].tradeProb
                    agents[agent_id]->tick(net, this);
                }
            }
            net = net + periodNet;
            priceHistory.push_back(getPrice());
            //Calculate current price and add to price_history
        }
        simResults.push_back(priceHistory);
        //Add price_history to simResults
    }
}

double Dealer::buyShares(double dollars){
    periodNet = periodNet + dollars;
    return dollars/getPrice();
};

double Dealer::sellShares(double shares){
    periodNet = periodNet - shares*getPrice();
    return shares*getPrice();
};

double Dealer::getPrice(){
    return exp(priceScale*net);
};
