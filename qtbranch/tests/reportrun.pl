#!/usr/bin/perl -wT

print "video,cascade,scale,faces,images,user,system,elapsed,cpu,pct,s/i\n";
my $r = 1;
while($_ = shift) {
	my $f = $_;
	@d = split '/', $f;
	print "${d[0]},${d[1]},${d[2]},";
	$#d -= 1;
	#results
	my $faces = 0,$images = 0;
	open my $rh, join( '/', @d)."/results";
	while (<$rh>) {
		$l = $_;
		next unless $l =~ /^Total\sFaces\s([0-9]+)\simages\s([0-9.]+)/;
		$faces=$1;
		$images=$2;
	}
	close ($rh);
	print "$faces,$images,";

	#times
	open my $fh, "<$f";
	while (<$fh>) {
		$l = $_;
		next unless $l =~ /^([0-9.]+)user\s([0-9.]+)system\s([0-9:.]+)elapsed\s([0-9]+)%CPU/;
		print "$1,$2,$3,$4,";
	}
	close ($fh);
	$r++;
	print "=d$r/e$r,=f$r/e$r\n";
}
