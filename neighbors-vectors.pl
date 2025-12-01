#!/usr/bin/perl

use strict;
use warnings;
use 5.022;


my $rates = {};
my $users_delta = {};


# loading dataset
while (my $str = <>) {
	chomp $str;
	my ($user_id, $content_id, $rate) = split /\t/, $str;
	$rates->{$user_id} //= {};
	$rates->{$user_id}->{$content_id} = $rate;
}


# calculationg users delta
for my $user_1 (keys %$rates) {
	for my $user_2 (keys %$rates) {
		next if $user_1 == $user_2;
		for my $c_id (keys %{$rates->{$user_1}}) {
			if (defined $rates->{$user_2}->{$c_id}) {
				my $r2 = $rates->{$user_2}->{$c_id};
				my $r1 = $rates->{$user_1}->{$c_id};
				my $delta = abs ($r2 - $r1);
				$users_delta->{$user_1} //= {};
				$users_delta->{$user_1}->{$user_2} //= 0;
				$users_delta->{$user_1}->{$user_2} += $delta;
			}
		}
	}
}

# finding nearest neighbors
my $neighbors = {};
for my $user_1 (keys %$users_delta) {
	for my $user_2 (%{$users_delta->{$user_1}}) {
		next unless $users_delta->{$user_1}->{$user_2};
		$neighbors->{$user_1} //= [];
		push @{$neighbors->{$user_1}}, [int ($user_2), $users_delta->{$user_1}->{$user_2}];
	}
	$neighbors->{$user_1} = [sort {$a->[1] <=> $b->[1]} @{$neighbors->{$user_1}}];
}

for (keys %$neighbors) {
	my $user_id = $_;
	for my $neighbors (@{$neighbors->{$user_id}}) {
		say "$user_id\t". join "\t", @$neighbors;
	}
}

1;
