//
//  model.h
//  zoo
//
//  Created by tianyuan wu on 2017/6/12.
//  Copyright © 2017年 tianyuan wu. All rights reserved.
//

#ifndef model_h
#define model_h
#include <iostream>
#include <limits.h>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

const double inf = std::numeric_limits<double>::infinity();




class cage {
public:
    cage() {}
    
    cage(long x, long y): x(x), y(y) {}
    
    const long getX() const{
        return x;
    }
    
    const long getY() const{
        return y;
    }
    
    bool isV() const{
        return isVisited;
    }
    
    short whosP() const {
        return parent;
    }
    
    double curPath() const{
        return pathWeight;
    }
    
    void updateParent(short newP) {
        parent = newP;
    }
    
    void visited() {
        isVisited = true;
    }
    
    void unvisited() {
        isVisited = false;
    }
    
    void updatePath(double newP) {
        pathWeight = newP;
    }
    
    
    
private:
    long x;
    long y;
    bool isVisited = false;
    short parent = -1;
    double pathWeight = inf;
    
    
    
};

class cageB {
public:
    cageB() {}
    
    cageB(long x, long y): x(x), y(y) {}
    
    const long getX() const{
        return x;
    }
    
    const long getY() const{
        return y;
    }
    
    bool isV() const{
        return isVisited;
    }
    
    void visited() {
        isVisited = true;
    }
    
    void unvisited() {
        isVisited = false;
    }
    

    
    
    
private:
    long x;
    long y;
    bool isVisited = false;
    
    
    
};


struct compByDis {
public:
    bool operator() (const cage& n1, const cage& n2) const {
        return n1.curPath() < n2.curPath();
    }
};

inline double disCal(cage& n1, cage& n2) {
    long x = n1.getX()-n2.getX();
    long y = n1.getY()-n2.getY();
    return sqrt((double)(x*x) + (double)(y*y));
}

class MST {
public:
    MST() {
        std::string inS;
        std:: cin >> inS;
        unsigned sz = std::stoi(inS);
        inputL.resize(sz);
        std::getline(std::cin, inS);
        
        unsigned counter = 0;
        std::string x, y;
        while (counter < sz) {
            std::cin >> x >> y;
            cage curN(std::stol(x), std::stol(y));
            inputL[counter++] = curN;
        }
    }
    
    // part A
    void initeForMST () {
        if (inputL.empty()) return;
        
        for (std::size_t i = 0; i < inputL.size(); ++i) {
            long x = inputL[i].getX();
            long y = inputL[i].getY();
            if (x > 0 || y > 0 || (x == 0 && y > 0) || (y == 0 && x > 0)) normalL.push_back((unsigned)i);
            else if (x < 0 && y < 0) wildL.push_back((unsigned)i);
            else edgeL.push_back((unsigned)i);
        }
        
    }
    
    void printMST(std::vector<short>& res) {
        if (totalDis == inf) {
            std::cout << "Cannot construct MST" <<std::endl;
            exit(1);
            
        }
        std::cout << totalDis << '\n';
        for (std::size_t i = 1; i < res.size(); ++i) {
            if (inputL[res[i]].whosP() < res[i]) std::cout << inputL[res[i]].whosP() << " " << res[i] << '\n';
            else std::cout << res[i] << " " <<  inputL[res[i]].whosP() << '\n';
            
        }
        
        
    }

    
    
    
    
    void genMST(std::ostringstream& os) {
        std::vector<short> path;
        path.resize(inputL.size());
        path[0] = 0;
        unsigned short curC = 0;
        inputL[curC].visited();
        inputL[0].updatePath(0);
        unsigned edgecounter = 0;
        unsigned completed = inputL.size() - 1;
        std::size_t idx = 0;
        

        while (edgecounter < completed) {
            
            long x = inputL[curC].getX();
            long y = inputL[curC].getY();
            if (x > 0 || y > 0 || (x == 0 && y > 0) || (y == 0 && x > 0)) {//normal set
                idx = 0;
                for (; idx < normalL.size(); ++idx) {
                    if (!inputL[normalL[idx]].isV()) {
                        double dis = disCal(inputL[curC], inputL[normalL[idx]]);
                        if (dis < inputL[normalL[idx]].curPath()) {
                            inputL[normalL[idx]].updateParent(curC);
                            inputL[normalL[idx]].updatePath(dis);
                        }
                        
                        
                    }
                }
                idx = 0;
                for (; idx < edgeL.size(); ++idx) {
                    if (!inputL[edgeL[idx]].isV()) {
                        double dis = disCal(inputL[curC], inputL[edgeL[idx]]);
                        if (dis < inputL[edgeL[idx]].curPath()) {
                            inputL[edgeL[idx]].updateParent(curC);
                            inputL[edgeL[idx]].updatePath(dis);
                        }
                        
                        
                    }
                }
            }
            
            else if (x < 0 && y < 0) {//wild set
                idx = 0;
                for (; idx < wildL.size(); ++idx) {
                    if (!inputL[wildL[idx]].isV()) {
                        double dis = disCal(inputL[curC], inputL[wildL[idx]]);
                        if (dis < inputL[wildL[idx]].curPath()) {
                            inputL[wildL[idx]].updateParent(curC);
                            inputL[wildL[idx]].updatePath(dis);
                        }
                        
                        
                    }
                }
                idx = 0;
                for (; idx < edgeL.size(); ++idx) {
                    if (!inputL[edgeL[idx]].isV()) {
                        double dis = disCal(inputL[curC], inputL[edgeL[idx]]);
                        if (dis < inputL[edgeL[idx]].curPath()) {
                            inputL[edgeL[idx]].updateParent(curC);
                            inputL[edgeL[idx]].updatePath(dis);
                        }
                        
                        
                    }
                }
            }
            
            else {//edge set
                idx = 0;
                for (; idx < normalL.size(); ++idx) {
                    if (!inputL[normalL[idx]].isV()) {
                        double dis = disCal(inputL[curC], inputL[normalL[idx]]);
                        if (dis < inputL[normalL[idx]].curPath()) {
                            inputL[normalL[idx]].updateParent(curC);
                            inputL[normalL[idx]].updatePath(dis);
                        }
                        
                        
                    }
                }
                idx = 0;
                for (; idx < wildL.size(); ++idx) {
                    if (!inputL[wildL[idx]].isV()) {
                        double dis = disCal(inputL[curC], inputL[wildL[idx]]);
                        if (dis < inputL[wildL[idx]].curPath()) {
                            inputL[wildL[idx]].updateParent(curC);
                            inputL[wildL[idx]].updatePath(dis);
                        }
                        
                        
                    }
                }
                idx = 0;
                for (; idx < edgeL.size(); ++idx) {
                    if (!inputL[edgeL[idx]].isV()) {
                        double dis = disCal(inputL[curC], inputL[edgeL[idx]]);
                        if (dis < inputL[edgeL[idx]].curPath()) {
                            inputL[edgeL[idx]].updateParent(curC);
                            inputL[edgeL[idx]].updatePath(dis);
                        }
                        
                        
                    }
                }
            }
            idx = 0;
            while (inputL[idx].isV()) ++idx;
            curC = idx;
            for (; idx < inputL.size(); ++idx) {
                if (!inputL[idx].isV() && inputL[idx].curPath() < inputL[curC].curPath())
                    curC = idx;
            }
            inputL[curC].visited();
            totalDis += inputL[curC].curPath();
            ++edgecounter;
            path[edgecounter] = curC;

        }
        
        printMST(path);
        
    }
    
    
    
    
private:
    std::vector<cage> inputL;
    double totalDis = 0;
    std::vector<unsigned> wildL;
    std::vector<unsigned> edgeL;
    std::vector<unsigned> normalL;
};

class FASTTSP {
public:
    
    FASTTSP() {
        std::string inS;
        std:: cin >> inS;
        unsigned sz = std::stoi(inS);
        inputL.resize(sz);
        std::getline(std::cin, inS);
        
        unsigned counter = 0;
        std::string x, y;
        while (counter < sz) {
            std::cin >> x >> y;
            cageB curN(std::stol(x), std::stol(y));
            inputL[counter++] = curN;
        }
    }
    
    double disCalB(cageB& n1, cageB& n2) {
        long x = n1.getX()-n2.getX();
        long y = n1.getY()-n2.getY();
        return sqrt((double)(x*x) + (double)(y*y));
    }
    
    // PARTB
    unsigned findClosest(cageB& c) {
        std::size_t res = 0;
        
        while (inputL[res].isV()) ++res;
        double shortestE = disCalB(c, inputL[res]);
        for (std::size_t i = res; i < inputL.size(); ++i) {
            if (!inputL[i].isV()) {
                double curE = disCalB(c, inputL[i]);
                if (curE <= shortestE) {
                    res = i;
                    shortestE = curE;
                }
            }
            
        }
        
        return (unsigned)res;
    }
    
    void optm(std::vector<unsigned>& path) {
        path.push_back(0);
        for (std::size_t i = 0; i < path.size() - 3; ++i) {
            for (std::size_t j = i + 2; j < path.size() - 1; ++j) {
                if ((disCalB(inputL[path[i]], inputL[path[i+1]]) +
                     (disCalB(inputL[path[j]], inputL[path[j+1]])) >
                     (disCalB(inputL[path[i]], inputL[path[j]]) +
                      disCalB(inputL[path[i + 1]], inputL[path[j + 1]])))) {
                         std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                         
                     }
            }
        }
        path.pop_back();
        
        
    }
    
    void genFTSP(std::ostringstream& os) {
        double totalDis = 0.0;
        std::vector<unsigned> res;
        res.resize(inputL.size());
        res[0] = 0;
        unsigned curC = 0;
        inputL[0].visited();
        unsigned eageCounter = 0;
        
        while (eageCounter < inputL.size() - 1) {
            unsigned next = findClosest(inputL[curC]);
            inputL[next].visited();
            curC = next;
            ++eageCounter;
            res[eageCounter] = next;
        }
        
        
        optm(res);
        //optm(res);
        
        
        for (std::size_t i = 0; i < res.size() - 1; ++i) {
            totalDis += disCalB(inputL[res[i]], inputL[res[i + 1]]);
            os << res[i] << " ";
        }
        totalDis += disCalB(inputL[res[0]], inputL[res[res.size() - 1]]);
        os << res.back() << " ";
        std::cout << totalDis << '\n' << os.str();
        
    }
    
private:
    std::vector<cageB> inputL;
};

class OPTTSP {
public:
    
    OPTTSP() {
        std::string inS;
        std:: cin >> inS;
        unsigned sz = std::stoi(inS);
        inputL.resize(sz);
        std::getline(std::cin, inS);
        
        unsigned counter = 0;
        std::string x, y;
        while (counter < sz) {
            std::cin >> x >> y;
            cage curN(std::stol(x), std::stol(y));
            inputL[counter++] = curN;
        }
    }
    // Part C
    unsigned findClosest(cage& c) {
        std::size_t res = 0;
        
        while (inputL[res].isV()) ++res;
        double shortestE = disCal(c, inputL[res]);
        for (std::size_t i = res; i < inputL.size(); ++i) {
            if (!inputL[i].isV()) {
                double curE = disCal(c, inputL[i]);
                if (curE <= shortestE) {
                    res = i;
                    shortestE = curE;
                }
            }
            
        }
        
        return (unsigned)res;
    }
    
    void optm(std::vector<short>& path) {
        path.push_back(0);
        for (std::size_t i = 0; i < path.size() - 3; ++i) {
            for (std::size_t j = i + 2; j < path.size() - 1; ++j) {
                if ((disCal(inputL[path[i]], inputL[path[i+1]]) +
                     (disCal(inputL[path[j]], inputL[path[j+1]])) >
                     (disCal(inputL[path[i]], inputL[path[j]]) +
                      disCal(inputL[path[i + 1]], inputL[path[j + 1]])))) {
                         std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                         
                     }
            }
        }
        path.pop_back();
        
        
    }

    void initeDisM() {
        disM.resize(inputL.size());
        for (std::size_t i = 0; i < disM.size(); ++i) {
            disM[i].resize(inputL.size());
            for (std::size_t j = 0; j < disM.size(); ++j)
                disM[i][j] = disCal(inputL[i], inputL[j]);
        }
        
        
    }
    
    double MSTcal(std::vector<short>& unvistied) {
        double res = 0.0;
        short curP = unvistied[0];
        inputL[curP].visited();
        short edgecounter = 0;
        short completed = unvistied.size() - 1;
        std::size_t idx;
        while (edgecounter < completed) {
            idx = 0;
            for (; idx < unvistied.size(); ++idx) {
                if (!inputL[unvistied[idx]].isV()) {
                    double dis = disM[curP][(unvistied[idx])];
                    if (dis < inputL[unvistied[idx]].curPath()) {
                        inputL[unvistied[idx]].updateParent(curP);
                        inputL[unvistied[idx]].updatePath(dis);
                    }
                    
                    
                }
            }
            
            idx = 0;
            while (inputL[unvistied[idx]].isV()) ++idx;
            curP = unvistied[idx];
            for (; idx < unvistied.size(); ++idx) {
                if (!inputL[unvistied[idx]].isV() && inputL[unvistied[idx]].curPath() < inputL[curP].curPath())
                    curP = unvistied[idx];
            }
            inputL[curP].visited();
            res += inputL[curP].curPath();
            ++edgecounter;
        }
        
        for (auto it = unvistied.begin(); it != unvistied.end(); ++it) {
            inputL[*it].unvisited();
            inputL[*it].updatePath(inf);
        }
        return res;
        
    }
    
    short findClose(short c, std::vector<short>& unvistied) {
        
        std::size_t res = 0;
        
        for (std::size_t i = 1; i < unvistied.size(); ++i) {
            if (disM[c][unvistied[i]] < disM[c][unvistied[res]]) res = i;
            
        }
        
        return unvistied[res];
    }
    
    
    double genLowerBound(short beginP, short endP, std::vector<short>& path,
                         std::vector<short>& unvistied) {
        
        return pathlen(path) + disM[beginP][findClose(beginP, unvistied)]
        + disM[endP][findClose(endP, unvistied)]+
        MSTcal(unvistied);
    }
    
    double calFTSP(std::vector<short>& res) {
        
        
        res.resize(inputL.size());
        res[0] = 0;
        short curC = 0;
        inputL[0].visited();
        short eageCounter = 0;
        
        while (eageCounter < inputL.size() - 1) {
            unsigned next = findClosest(inputL[curC]);
            inputL[next].visited();
            curC = next;
            ++eageCounter;
            res[eageCounter] = next;
        }
        inputL[curC].updatePath(disCal(inputL[0], inputL[curC]));
        inputL[curC].updateParent(0);
        
        
        optm(res);
        //optm(res);
        
        
        double fastW = 0.0;
        for (std::size_t i = 0; i < res.size() - 1; ++i) {
            fastW += disCal(inputL[res[i]], inputL[res[i + 1]]);
        }
        fastW += disM[res[0]][res.back()];
        for (std::size_t i = 0; i < inputL.size(); ++i) {
            inputL[i].unvisited();
        }
        return fastW;
        
    }
    
    
    bool promising(std::deque<short>& unused, std::vector<short>& path,const double& upperbound) {
        if (unused.size() < 5) return true;
        std::vector<short> worklist(unused.begin(), unused.end());
        return genLowerBound(path.front(), path.back(), path, worklist) <= upperbound;
    }
    
    double pathlen(std::vector<short> &path) {
        double res = 0.0;
        for(std::size_t i = 0; i < path.size() - 1; ++i) {
            res += disM[path[i]][path[i+1]];
        }
        
        
        return res;
        
    }
    
    void genPerms(std::deque<short> &unused, std::vector<short> &path,
                  std::vector<short> &res, double& upperbound) {
        if (unused.empty()) {
            double curL = (pathlen(path) + disM[0][path.back()]);
            if (curL <= (pathlen(res) + disM[0][res.back()])) {
                res = path;
                upperbound = curL;
            }
            return;
            
        } // if
        
        if (!promising(unused, path, upperbound)) return;
        for (unsigned k = 0; k != unused.size(); k++) {
            path.push_back(unused.front());
            unused.pop_front();
            genPerms(unused, path, res, upperbound);
            unused.push_back(path.back());
            path.pop_back();
        } // for
    }
    
    void genOPTTSP(){
        double totalDis = 0.0;
        initeDisM();
        std::vector<short> res;
        double fastW = calFTSP(res);
//        if (res.size() > 25) fastW *= 0.98;
//        else if (res.size() > 35) fastW *= 0.95;
        std::deque<short> unused;
        for (std::size_t i = 0; i < inputL.size() - 1; ++i) {
            unused.push_back(i+1);
        }
        std::vector<short> path;
        path.push_back(0);
        inputL[0].visited();
//        short next = findClosest(inputL[0]);
//        path.push_back(next);
//        unused.erase(std::find(unused.begin(), unused.end(), next));
        
        
        genPerms(unused, path, res, fastW);
        
        
        totalDis += pathlen(res);
        totalDis += disM[0][res.back()];
        
        std::cout << totalDis << '\n';
        for (auto it = res.begin(); it != res.end(); ++it) std::cout << *it << " ";
    }
    
private:
    std::vector<cage> inputL;
    std::vector<std::vector<double>> disM;
    
    
};

#endif /* model_h */
