#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{

    base = baseim;
    maze = mazeim;
    start = s;

}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

    RGBAPixel* toChange = im.getPixel(loc.first, loc.second);

    toChange->r = 2*(toChange->r / 4);
    toChange->g = 2*(toChange->g / 4);
    toChange->b = 2*(toChange->b / 4);

    // toChange->r = 255;
    // toChange->g = 0;
    // toChange->b = 0;

}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

    RGBAPixel* toChange = im.getPixel(loc.first, loc.second);

    unsigned char encode = d % 64;
    
    unsigned char encR = encode & 0x30; // 0011 0000
    encR = encR >> 4;
    unsigned char encG = encode & 0x0c; // 0000 1100
    encG = encG >> 2;
    unsigned char encB = encode & 0x03; // 0000 0011

    toChange->r = ((toChange->r & 0xfc) | encR);
    toChange->g = ((toChange->g & 0xfc) | encG);
    toChange->b = ((toChange->b & 0xfc) | encB);

}

PNG treasureMap::renderMap() {

    PNG baseNew = base;

    vector<bool> innerB;
    vector<int> innerI;

    vector<vector<bool>> visited;
    vector<vector<int>> lengths;
    Queue<pair<int, int>> locations;

    innerB.resize(baseNew.height());
    innerI.resize(baseNew.height());

    for (unsigned int i = 0; i < baseNew.width(); i++) {
        visited.push_back(innerB);
        lengths.push_back(innerI);
    }


    visited[start.first][start.second] = true;
    lengths[start.first][start.second] = 0;
    setLOB(baseNew, start, 0);    
    locations.enqueue(start);

    

    while (!locations.isEmpty()) {

        pair<int, int> curr = locations.dequeue();

        int currX = curr.first;
        int currY = curr.second;

        int d = lengths[currX][currY];

        vector<pair<int, int>> nexts = neighbors(curr);

        for (int i = 0; i < nexts.size(); i++) {
            if (good(visited, curr, nexts[i])) {
                visited[nexts[i].first][nexts[i].second] = true;
                lengths[nexts[i].first][nexts[i].second] = d + 1;
                setLOB(baseNew, nexts[i], d + 1);
                locations.enqueue(nexts[i]);
            }
        }
    }

    return baseNew;



}


PNG treasureMap::renderMaze() {

    PNG baseNew = base;


    vector<vector<bool>> visited;
    vector<bool> innerB;

    innerB.resize(baseNew.height());

    for (unsigned int i = 0; i < baseNew.width(); i++) {
        visited.push_back(innerB);
    }
    visited[start.first][start.second] = true;

    Queue<pair<int, int>> locations;

    locations.enqueue(pair<int,int>(start.first, start.second));

    while (!locations.isEmpty()) {
        pair<int, int> curr = locations.dequeue();
        vector<pair<int, int>> nexts = neighbors(curr);
        for (auto next : nexts) {
            if (good(visited, curr, next)) {
                visited[next.first][next.second] = true;
                setGrey(baseNew, next);
                locations.enqueue(next);
            }
        }
    }





    for (int j = start.second - 3; j <= start.second + 3; j++) {
        if (j >= 0 && j < baseNew.height()) {
            for (int i = start.first - 3; i <= start.first + 3; i++) {
                if (i >= 0 && i < baseNew.width()) {
                    RGBAPixel* setRed = baseNew.getPixel(i, j);
                    setRed->r = 255;
                    setRed->g = 0;
                    setRed->b = 0;

                }
            }
        }
    }

    return baseNew;


}



bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    int x = next.first;
    int y = next.second;
    if (!(x >= 0 && x < maze.width() && y >= 0 && y < maze.height())) {
        return false;
    }

    if (v[x][y]) {
        return false;
    }
    RGBAPixel* compare1 = maze.getPixel(curr.first, curr.second);
    RGBAPixel* compare2 = maze.getPixel(x, y);
    if (!(compare1->r == compare2->r
    && compare1->g == compare2->g
    && compare1->b == compare2->b)) {
        return false;
    }

    return true;


}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* YOUR CODE HERE */
    vector<pair<int, int>> nexts;

    int currX = curr.first;
    int currY = curr.second;

    pair<int,int> left(currX - 1, currY);
    pair<int,int> right(currX + 1, currY);
    pair<int,int> up(currX, currY + 1);
    pair<int,int> down(currX, currY - 1);

    nexts.push_back(left);
    nexts.push_back(right);
    nexts.push_back(up);
    nexts.push_back(down);

    return nexts;

}

