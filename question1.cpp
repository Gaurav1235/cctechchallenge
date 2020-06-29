#include <iostream> 
#include <bits/stdc++.h>
using namespace std; 
  
#define INF 100000.0 
#define pdd pair<double,double>  

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool on_the_same_Segment(pdd p, pdd q, pdd r) 
{ 
    if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) && 
            q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second)) 
        return true;
    return false; 
} 
  
int orientation(pdd p, pdd q, pdd r) 
{ 
    double val = (q.second - p.second) * (r.first - q.first) - 
              (q.first - p.first) * (r.second - q.second); 
  
    if (val == 0) return 0;  // colinear 
    if(val>0)   // 1-clockwise or 2-counterclock wise 
        return 1;
    else 
        return 2;
    
} 
  
// to check whether p1,q1 and p2,q2 intersect or not
bool doIntersect(pdd p1, pdd q1, pdd p2, pdd q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int w1 = orientation(p1, q1, p2); 
    int w2 = orientation(p1, q1, q2); 
    int w3 = orientation(p2, q2, p1); 
    int w4 = orientation(p2, q2, q1); 
  
    // General case 
    if (w1 != w2 && w3 != w4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (w1 == 0 && on_the_same_Segment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (w2 == 0 && on_the_same_Segment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (w3 == 0 && on_the_same_Segment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (w4 == 0 && on_the_same_Segment(p2, q1, q2)) return true; 
  
    return false; // else return false 
} 
bool inside_outside(vector<pdd> &polygon, pdd p) 
{ 
    // for polygon having size less than 3 return false
    int n=polygon.size();
    if (n < 3)  return false; 
  
    // Create a point for line segment from p to infinite 
    pdd extreme = {INF, p.second}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 
  
        // to check whether line segment (polygon[i],polygon[next] ) and (p,extreme) intersects or not
        if (doIntersect(polygon[i], polygon[next], p, extreme)) 
        { 
            // If the point 'p' is colinear with line segment (polygon[i],polygon[next]), 
            // then check if it lies on segment. If it lies, return true, // because point on the border is considered to be inside
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
               return on_the_same_Segment(polygon[i], p, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    if(count%2!=0)
        return 1;
    else 
        return 0;
} 
  
// Driver program to test above functions 
int main() 
{ 
    
    int n;
    cin>>n;
    vector<pair<double,double>> polygon;
    while(n--){
        double i,j;
        cin>>i>>j;
        polygon.push_back({i,j});
    }
    double i,j;
    cin>>i>>j;
    pdd p = {i, j}; 
    cout<<inside_outside(polygon, p);
  
  
    return 0; 
}