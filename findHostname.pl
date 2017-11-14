###########################################################
#
# Skript zur Bestimmung der DNS-Namen von SicherHTTPD logs
#
###########################################################


use strict;
use warnings;


sub dnsLookup
{
   my $ip=$_[0];


  open(my $fh, '-|', "host $ip") or die $!;
  my $line = <$fh>;
  if( $line =~ /.* name pointer ([\S]+)\./ )
  {
    return $1
  }
  else
  {  
    return $ip;
  }
}

my %hostnames = ();

while(<STDIN>)
{
   my $line = $_;
 
   #print("$line");

   if( $line =~ /^(.*) GET ([0-9\.]+) ([a-zA-Z\/\.0-9]+)/ )
   {
       my $datum = $1;
       my $ip = $2;
       my $url = $3;

       #print("$datum $ip $url\n");

       if( !exists($hostnames{$ip}) )
       {
          $hostnames{$ip} = dnsLookup($ip);           
       }
       print("$datum $hostnames{$ip} $url\n");
   }
}
