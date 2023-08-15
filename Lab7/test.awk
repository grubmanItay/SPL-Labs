#! /usr/bin/awk -f
#BEGIN { OFS = "|"
#	FS = ","}
#{ print $4, $3, $2 } 

BEGIN { FS = ","
	OFS = "|"}
{ if ($2 >= 1970 && $1 > 43)
  {print "—-------------------------------"
  print $0
  print $1}
}

#BEGIN { FS = ","}
#{ if ($1 >= 50 && $1 <= 70)
#  {print "—-------------------------------"
#  print "Movie Name: " $5}
#}

#BEGIN {for (i = 0; i < ARGC; i++)
 #           print "argv[" i "] = " ARGV[i]}
