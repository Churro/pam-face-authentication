#!/usr/bin/perl -wT

print "LX,LY,RX,RY,L\n";
my $r = 1;
while(<>) {
	$l = $_;
	next unless $l =~ /^Eyes\sLen\s\(([0-9]+)\)\sLE\s@\(([0-9]+),([0-9]+)\)\sRE\s@\(([0-9]+),([0-9]+)\)$/;
		print "$2,$3,$4,$5,$1\n";
}
