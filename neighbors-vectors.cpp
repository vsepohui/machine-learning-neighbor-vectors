#include <iostream>
#include <map>

std::map <int,std::map<int, int>> rates;
std::map <int,std::map<int, int>> users_delta;



int main () {
	int user_id, content_id, rate;
	
	// loading dataset
	while (std::cin >> user_id >> content_id >> rate) {
		rates[user_id][content_id] = rate;
	}
	
	map <int, std::map<int, int>>::iterator user_1, user_2;
	map <int, int>::iterator content_id;
	
	for (user_1 = rates.begin(); user_1 != rates.end(); user_1++) {
		for (user_2 = rates.begin(); user_2 != rates.end(); user_2++) {
			for (content_id = rates[user_1].begin(); content_id != rates[user_1].end(); content_id++) {
				if (rates[user_2].contains(content_id)) {
					int r2 = rates[user_2][content_id];
					int r1 = rates[user_1][content_id];
					int delta = abs(r2 - r1);
					users_delta[user_1][user_2] ||= 0;
					users_delta[user_1][user_2] += delta;
				}
			}
		}
	}
	
	// finding nearest neighbors
	
}


/*
# finding nearest neighbors
my $neighbors = {};
for my $user_1 (keys %$users_delta) {
	for my $user_2 (%{$users_delta->{$user_1}}) {
		next unless $users_delta->{$user_1}->{$user_2};
		$neighbors->{$user_1} //= [];
		push @{$neighbors->{$user_1}}, [$user_2, $users_delta->{$user_1}->{$user_2}];
	}
	$neighbors->{$user_1} = [sort {$a->[1] <=> $b->[1]} @{$neighbors->{$user_1}}];
}


1;

*/
