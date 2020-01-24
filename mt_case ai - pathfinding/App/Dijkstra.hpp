#pragma once

#include "Lib.hpp"
#include <algorithm>
#include <unordered_map>

using namespace std; 
namespace std {

	template <>
	struct hash<Vector2i> {
		std::size_t operator()(const Vector2i& k) const 
		{
			return (unsigned int)(k.x << 16) | ((unsigned int)k.y);
		}
	};

	template <>
	struct hash<Vector2f> {
		std::size_t operator()(const Vector2f& k) const 
		{
			return (unsigned int)((int)k.x << 16) | ((unsigned int)k.y);
		}
	};

}

class Dijkstra {
public : 
	std::vector<Vector2f> G;
	std::unordered_map<Vector2f, float> distance;
	std::unordered_map<Vector2f, Vector2f> pred;
	Vector2f dep;

	void Init(const std::vector<Vector2f>& _G, const Vector2f _dep) {
		G = _G;
		dep = _dep;

		for(const Vector2f& vec : _G) 
		{
			distance[vec] = 999999999;
		}
		distance[dep] = 0;
	}

	Vector2f find_min(std::vector<Vector2f>& queue) 
	{
		int mini = 999999999;
		Vector2f sommet = Vector2f(-999999999,-999999999);
		for (Vector2f vec : queue) 
		{
			if (distance[vec] < mini) {
				mini = distance[vec];
				sommet = vec;
			}
		}
		return sommet;
	}

	float poua(Vector2f s1, Vector2f s2) 
	{
		return sqrt(((s2.x-s1.x)*(s2.x - s1.x)) + ((s2.y - s1.y)*(s2.y - s1.y)));
	}

	void maj_distances(Vector2f s1, Vector2f s2) 
	{
		if (distance[s2] > distance[s1] + poua(s1, s2)) 
		{
			distance[s2] = distance[s1] + poua(s1, s2);
			pred[s2] = s1;
		}
	}

	std::vector<Vector2f> CALCULATE(const std::vector<Vector2f>& _G, const Vector2f _dep, const Vector2f fin)
	{
		Init(_G, _dep);
		std::vector<Vector2f> Q = G;
		while (Q.size() > 0)
		{
			Vector2f s1 = find_min(Q);

			std::vector<Vector2f>::iterator it;
			it = std::find(Q.begin(), Q.end(), s1);
			if (it != Q.end()) Q.erase(it);

			/*std::vector<Vector2f> _Q;
			for (int i = 0; i < Q.size(); i++)
			{
				if (Q[i] != s1)_Q.push_back(Q[i]);
			}
			Q = _Q;*/

			

			if (distance.find(s1 + Vector2f(0, 1)) != distance.end()) maj_distances(s1, s1 + Vector2f(0, 1));
			if (distance.find(s1 - Vector2f(0, 1)) != distance.end()) maj_distances(s1, s1 - Vector2f(0, 1));
			if (distance.find(s1 + Vector2f(1, 0)) != distance.end()) maj_distances(s1, s1 + Vector2f(1, 0));
			if (distance.find(s1 - Vector2f(1, 0)) != distance.end()) maj_distances(s1, s1 - Vector2f(1, 0));
		}

		Vector2f s = fin;
		std::vector<Vector2f> A;

		while (s != dep)
		{
			A.push_back(s);
			s = pred[s];
		}
		return A;
	}

	std::vector<Vector2f> FindPCC(const Vector2f fin) {
		Vector2f s = fin;
		std::vector<Vector2f> A;

		while (s != dep)
		{
			A.push_back(s);
			s = pred[s];
		}
		return A;
	}


//ASTAR


	std::vector<Vector2f> reconstructpath(std::unordered_map<Vector2f, Vector2f> camefrom, Vector2f current)
	{
		std::vector<Vector2f> A;
		//A.push_back(current);
		while (camefrom.find(current) != camefrom.end()) 
		{
			A.push_back(current);
			current = camefrom[current];
		}
		return A;
	}



	Vector2f getmin(std::vector<Vector2f> dist, std::unordered_map<Vector2f, float> dist2)
	{
		Vector2f a;
		int min = 999999999;
		for (Vector2f key : dist)
		{
			if (dist2[key] < min) {
				min = dist2[key];
				a = key;
			}
		}
		return a;
	}



	std::vector<Vector2f> Astar(const std::vector<Vector2f>&_G, const Vector2f _dep, const Vector2f fin)
	{
		int counter = 100;
		std::vector<Vector2f> G2 = { _dep };
		Vector2f a = _dep;
		std::unordered_map<Vector2f, Vector2f> pred2;
		std::unordered_map<Vector2f, float> distancebest;
		for (const Vector2f& vec : _G)
		{
			distancebest[vec] = 999999999;
		}
		distancebest[a] = 0;

		std::unordered_map<Vector2f, float> distance2;
		for (const Vector2f& vec : _G)
		{
			distance2[vec] = 999999999;
		}
		distance2[a] = poua(a,fin);

		while (G2.size() != 0) 
		{
			Vector2f current = getmin(G2, distance2);
			if (counter == 0 || current == fin) return reconstructpath(pred2, current);

			std::vector<Vector2f>::iterator it;
			it = std::find(G2.begin(), G2.end(), current);
			if (it != G2.end()) G2.erase(it);

			if ( distancebest.find(current + Vector2f(0, 1)) != distancebest.end())
			{ 
				Vector2f neighbor = current + Vector2f(0, 1);
				float zbleh = distancebest[current] + poua(current, neighbor);
				if (zbleh < distancebest[neighbor])
				{
					pred2[neighbor] = current;
					distancebest[neighbor] = zbleh;
					distance2[neighbor] = distancebest[neighbor] + poua(neighbor, fin);
					if (std::find(G2.begin(), G2.end(), neighbor) == G2.end()) G2.push_back(neighbor);
				}
			}

			if ( distancebest.find(current - Vector2f(0, 1)) != distancebest.end())
			{
				Vector2f neighbor = current - Vector2f(0, 1);
				float zbleh = distancebest[current] + poua(current, neighbor);
				if (zbleh < distancebest[neighbor])
				{
					pred2[neighbor] = current;
					distancebest[neighbor] = zbleh;
					distance2[neighbor] = distancebest[neighbor] + poua(neighbor, fin);
					if (std::find(G2.begin(), G2.end(), neighbor) == G2.end()) G2.push_back(neighbor);
				}
			}

			if ( distancebest.find(current + Vector2f(1, 0)) != distancebest.end())
			{
				Vector2f neighbor = current + Vector2f(1, 0);
				float zbleh = distancebest[current] + poua(current, neighbor);
				if (zbleh < distancebest[neighbor])
				{
					pred2[neighbor] = current;
					distancebest[neighbor] = zbleh;
					distance2[neighbor] = distancebest[neighbor] + poua(neighbor, fin);
					if (std::find(G2.begin(), G2.end(), neighbor) == G2.end()) G2.push_back(neighbor);
				}
			}

			if ( distancebest.find(current - Vector2f(1, 0)) != distancebest.end())
			{
				Vector2f neighbor = current - Vector2f(1, 0);
				float zbleh = distancebest[current] + poua(current, neighbor);
				if (zbleh < distancebest[neighbor])
				{
					pred2[neighbor] = current;
					distancebest[neighbor] = zbleh;
					distance2[neighbor] = distancebest[neighbor] + poua(neighbor, fin);
					if (std::find(G2.begin(), G2.end(), neighbor) == G2.end()) G2.push_back(neighbor);
				}
			}
			counter -= 1;	
		}
	}
};