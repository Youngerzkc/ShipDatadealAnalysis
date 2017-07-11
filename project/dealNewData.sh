
#处理新的数据

for newfile in ./newShipInformation/*
 do 
 	if test -d $newfile
	 then 
	 # echo $newfile
	  pwd
	  else
	  	mkdir -p ./waitJudge/$newfile
			echo $newfile
	
	    ./sort $newfile
	    ./readTxt $newfile
	    rm -rf rebuild	
	    mkdir rebuild	
	    cp data.txt ./validShipInformation/$newfile/
	    cp speed_zero.txt ./validShipInformation/$newfile/
	    rm -rf data.txt 
	    mv speed_zero.txt ./rebuild/speed_zero

		cd ./rebuild
	    ../choose_zero_block speed_zero

	    for newpack in ../rebuild/*
   		 do
			if test -d $newpack
			then
		#	echo $newpack
		pwd 
			else
			../new_valid_pack $newpack
       		fi
   		 done
		cd ..
		cp ./rebuild/*.txt ./waitJudge/$newfile/
		rm -rf ./rebuild 
		for matchfile in ./waitJudge/$newfile/*
		do 
			if test -d  $matchfile
			then 
		#	echo $matchfile
		pwd
			else
			cd ./portBlock
			
		   for bound in *
	       do 
	    		if test -d $bound
		  	 then 
	    	#	echo $bound	
		  		../jugdeBoundary $bound ../waitJudge/$newfile/$matchfile	
				fi
 			done
			     cd ..
	        fi
      done 
	fi 
done

