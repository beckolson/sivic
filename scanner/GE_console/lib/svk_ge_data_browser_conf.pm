#!/usr/bin/perl -w

#
#   Copyright © 2009-2014 The Regents of the University of California.
#   All Rights Reserved.
# 
#   Redistribution and use in source and binary forms, with or without 
#   modification, are permitted provided that the following conditions are met:
#   •   Redistributions of source code must retain the above copyright notice, 
#       this list of conditions and the following disclaimer.
#   •   Redistributions in binary form must reproduce the above copyright notice, 
#       this list of conditions and the following disclaimer in the documentation 
#       and/or other materials provided with the distribution.
#   •   None of the names of any campus of the University of California, the name 
#       "The Regents of the University of California," or the names of any of its 
#       contributors may be used to endorse or promote products derived from this 
#       software without specific prior written permission.
#   
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
#   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
#   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
#   IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
#   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
#   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
#   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
#   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
#   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
#   OF SUCH DAMAGE.
# 

#   $URL: svn+ssh://jccrane@svn.code.sf.net/p/sivic/code/trunk/libs/src/svkImageData.cc $
#   $Rev: 1741 $
#   $Author: jccrane $
#   $Date: 2014-02-19 11:28:48 -0800 (Wed, 19 Feb 2014) $
# 
#   Authors:
#       Jason C. Crane, Ph.D.
#       Beck Olson
# 


package svk_ge_data_browser_conf;
use strict;
use lib "$ENV{HOME}/svk/lib";
use svk_ge_util;

sub svk_ge_get_tail($); 

#
#   Global lookup table between local values of
#   $HOST and registered hostnames on svk_ge network.
#
%svk_ge_data_browser_conf::network_hostnames = (
    'qb3-3t'                    =>  'qb3-mr3t',
    'qb3-7t'                    =>  'qb3-mr7t',
    'mrc1-ow'                   =>  'mrc1_oc0',
    'CB-3TMR'                   =>  'cb-mr3t',
    'scalar.radiology.ucsf.edu' =>  'scalar',
    'mrc2'                      =>  'mrc2',
    'UCSF-MRN2'                 =>  'ucsf-mrn2', 
    'UCSF-MRN1'                 =>  'ucsf-mrn1', 
    'icn1'                      =>  'icn1'
);


#
#   The remote host acting as the submit host:  should be accessible from scanner:
#
my $remote_host_QB3 = "borealis";
my $remote_host_CB = "avalanche.radiology.ucsf.edu";
my $remote_host_PARNASSUS = "avalanche.radiology.ucsf.edu";

%svk_ge_data_browser_conf::remote_host = (
    'qb3-3t'                    =>  "$remote_host_QB3",
    'qb3-7t'                    =>  "$remote_host_QB3",
    'scalar.radiology.ucsf.edu' =>  "$remote_host_QB3",
    'CB-3TMR'                   =>  "$remote_host_CB",
    'mrc1-ow'                   =>  "$remote_host_PARNASSUS", 
    'mrc2'                      =>  "$remote_host_PARNASSUS", 
    'UCSF-MRN2'                 =>  "$remote_host_PARNASSUS", 
    'UCSF-MRN1'                 =>  "$remote_host_PARNASSUS"
);


#
#   VRE (volume recon engine) compute node (aka ICN - image compute node).  
#
my $VRE_host = "icn2";
%svk_ge_data_browser_conf::VRE_host = (
    'qb3-3t'                    =>  "$VRE_host",
    'qb3-7t'                    =>  "icn1",
    'CB-3TMR'                   =>  "$VRE_host", 
    'mrc2'                      =>  "$VRE_host", 
    'UCSF-MRN2'                 =>  "$VRE_host", 
    'UCSF-MRN1'                 =>  "$VRE_host" 
);


# 
#   set up work path tail: scanner_host_name/script_name 
# 
my $script_name = svk_ge_get_tail($0);
my $dir_tail = "$svk_ge_data_browser_conf::network_hostnames{$ENV{HOST}}/$script_name";


#
#   The remote data directory 
#
$svk_ge_data_browser_conf::remote_data_dir = "/data/lhst3/scanner_data/$dir_tail";


#
#   The work dir on the scanner:
#	/root/host_name/script_name
#
if ( defined $ENV{SDCHOME} ) {
    $svk_ge_data_browser_conf::scanner_work_dir = "$ENV{SDCHOME}/svk/data/$dir_tail";
} else {
    # VRE: 	
    $svk_ge_data_browser_conf::scanner_work_dir = "/export/home/sdc/svk/data/$dir_tail";
}


#
#   The work dir on the scanner:
#	/root/host_name/script_name
#
$svk_ge_data_browser_conf::vre_bin_dir = "/export/home/sdc/svk/bin";


sub svk_ge_get_tail($)
{
    my $path = $_[0];
    my $tail;

    if ($path =~ /.*\/(\S+)$/) {
        $tail = $1;
    }
    else {
        $tail = $path;
    }

    return $tail;
}
