#include <iostream>
#include <map>
#include <vector>



int main () {

	std::map <int,std::map<int, int>> rates;
	std::map <int,std::map<int, int>> users_delta;

	
	// loading dataset
	int _user_id, _content_id, _rate;
	while (std::cin >> _user_id >> _content_id >> _rate) {
		rates[_user_id][_content_id] = _rate;
	}
	


	
	std::map <int, std::map<int, int>>::iterator user_1, user_2;
	std::map <int, int>::iterator content_id;
	
	for (user_1 = rates.begin(); user_1 != rates.end(); user_1++) {
		for (user_2 = rates.begin(); user_2 != rates.end(); user_2++) {
			if (user_1->first == user_2->first) {
				continue;
			}
			
			for (content_id = rates[user_1->first].begin(); content_id != rates[user_1->first].end(); content_id++) {
				if (rates[user_2->first][content_id->first]) {
					int r2 = rates[user_2->first][content_id->first];
					int r1 = rates[user_1->first][content_id->first];
					int delta = abs(r2 - r1);
					if (!users_delta[user_1->first][user_2->first]) {
						users_delta[user_1->first][user_2->first] = 0;
					}
					users_delta[user_1->first][user_2->first] += delta;
				}
			}
		}
	}
	

	// finding nearest neighbors
	std::map <int,std::vector<int*>> neighbors;
	
	for (user_1 = users_delta.begin(); user_1 != users_delta.end(); user_1++) {
		for (user_2 = users_delta.begin(); user_2 != users_delta.end(); user_2++) {
			if (!users_delta[user_1->first][user_2->first]) {
				continue;
			}
			int delta[2] = {(int)user_2->first, users_delta[user_1->first][user_2->first]};
			neighbors[user_1->first].push_back(delta);
		}
		

	}
	
	
	std::map <int, std::vector<int*>>::iterator neighbors_id;
	for (neighbors_id = neighbors.begin(); neighbors_id != neighbors.end(); neighbors_id++) {
		int user_id = neighbors_id->first;
		std::vector<int*> n = neighbors[user_id];
		
		std::vector <int*>::iterator nv_id;
		int i = 0;
		for (nv_id = n.begin(); nv_id != n.end(); nv_id++) {
			int *d = n[i];
			int user_2 = d[0];
			int delta  = d[1];
			std::cout << user_id << "\t" << user_2 << "\t" << delta << "\n";
			i ++;
		}		
	}
	
	//std::cout << neighbors[1][0][1] << "\n";
	//std::cout << neighbors[1][1][1] << "\n";
	//std::cout << neighbors[1][2][0] << "\n";
	
}


/*


1;

*/
