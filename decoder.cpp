#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

   start = s;
   mapImg = tm;
   pathPts.push_back(start);

   vector<pair<int, int>> filling;

   vector<int> length_filling;
   vector<bool> visit;

   // vector<vector<int>> lengths;
   vector<vector<bool>> visited;



   filling.resize(mapImg.height());
   length_filling.resize(mapImg.height());
   visit.resize(mapImg.height());

   for (int i = 0; i < mapImg.width(); i++) {
      prevLocs.push_back(filling);
      visited.push_back(visit);
      lengths.push_back(length_filling);
   }

   // starts prevLocation = itself
   prevLocs[start.first][start.second] = start;
   lengths[start.first][start.second] = 0;
   visited[start.first][start.second] = true;
   


   Queue<pair<int, int>> locations;
   locations.enqueue(start);

   while (!locations.isEmpty()) {

      pair<int, int> curr = locations.dequeue();

      int currX = curr.first;
      int currY = curr.second;

      int d = lengths[currX][currY];

      vector<pair<int, int>> nexts = neighbors(curr);

      // updates arrays with correct values
      for (int i = 0; i < nexts.size(); i++) {
         if (good(visited, lengths, curr, nexts[i])) {
               visited[nexts[i].first][nexts[i].second] = true;
               lengths[nexts[i].first][nexts[i].second] = d + 1;
               prevLocs[nexts[i].first][nexts[i].second] = curr;
               locations.enqueue(nexts[i]);
         }
      }
    }
      pair<int, int> max;
      int maxSoFar = -1;

      // finds x, y of longest spot
      for (int y = 0; y < mapImg.height(); y++) {
         for (int x = 0; x < mapImg.width(); x++) {
            if (lengths[x][y] > maxSoFar) {
               maxSoFar = lengths[x][y];
               max = make_pair(x, y);
            }
         }
      } 

      pair<int, int> next = max;
      Stack<pair<int, int>> path;

      // traverses from the treasure to the start using prevLocs
      while (!(next.first == start.first && next.second == start.second)) {
         path.push(next);
         next = prevLocs[next.first][next.second];
      }

      // uses the stack and builds pathPts
      while (!path.isEmpty()) {
         pathPts.push_back(path.pop());
      }
}

PNG decoder::renderSolution(){

   PNG copy = mapImg;

   for (int i = 0; i < pathPts.size(); i++) {
      RGBAPixel* curr = copy.getPixel(pathPts[i].first, pathPts[i].second);
      curr->r = 255;
      curr->g = 0;
      curr->b = 0;
      
   }

   return copy;

}

PNG decoder::renderMaze(){

   PNG copy = mapImg;

   vector<vector<bool>> visited;
   vector<bool> innerB;

   innerB.resize(mapImg.height());

   for (unsigned int i = 0; i < mapImg.width(); i++) {
      visited.push_back(innerB);
   }
   visited[start.first][start.second] = true;

   Queue<pair<int, int>> locations;

   locations.enqueue(pair<int,int>(start.first, start.second));

   while (!locations.isEmpty()) {
      pair<int, int> curr = locations.dequeue();
      vector<pair<int, int>> nexts = neighbors(curr);
      for (auto next : nexts) {
         if (good(visited, lengths, curr, next)) {
               visited[next.first][next.second] = true;
               setGrey(copy, next);
               locations.enqueue(next);
         }
      }
   }

   for (int j = start.second - 3; j <= start.second + 3; j++) {
      if (j >= 0 && j < mapImg.height()) {
         for (int i = start.first - 3; i <= start.first + 3; i++) {
               if (i >= 0 && i < mapImg.width()) {
                  RGBAPixel* setRed = copy.getPixel(i, j);
                  setRed->r = 255;
                  setRed->g = 0;
                  setRed->b = 0;

               }
         }
      }
   }

   return copy;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){

   RGBAPixel* toChange = im.getPixel(loc.first, loc.second);

    toChange->r = 2*(toChange->r / 4);
    toChange->g = 2*(toChange->g / 4);
    toChange->b = 2*(toChange->b / 4);

}

pair<int,int> decoder::findSpot(){

   return pathPts[pathPts.size() - 1];

}

int decoder::pathLength(){

   return pathPts.size();

}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

   int x = next.first;
   int y = next.second;
   if (!(x >= 0 && x < mapImg.width() && y >= 0 && y < mapImg.height())) {
      return false;
   }

   if (v[x][y]) {
      return false;
   }

   RGBAPixel* pos = mapImg.getPixel(x, y);


   if (!compare(*pos, d[curr.first][curr.second])) {
      return false;
   }

   return true;


}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

   vector<pair<int, int>> nexts;

    int currX = curr.first;
    int currY = curr.second;

    pair<int,int> left(currX - 1, currY);
    pair<int,int> right(currX + 1, currY);
    pair<int,int> up(currX, currY + 1);
    pair<int,int> down(currX, currY - 1);

    nexts.push_back(left);
    nexts.push_back(down);
    nexts.push_back(right);
    nexts.push_back(up);

    return nexts;

}


bool decoder::compare(RGBAPixel p, int d){

   unsigned int p2 = (p.r % 4) * 16 + (p.g % 4) * 4 + (p.b % 4);

   return (p2 % 64) == ((d + 1) % 64);

}
