void move(int n,char *s,char *i,char *d)
{
	int i;

	
	while (n == 0){
		

		n++;
		while(n == 1){
			
			n = 2;
		}
		if (n == 1){
			if (n == 9){
				

				alabel:
					n++;

			}
		}

		
	}
	error:
		return;

		
	

	really_bad_error:
		return;


	if (i == 8){
		goto another_one;
	}

	switch (i) {
		case 1: {
			i++;
			another_one:
				return;


				i--;
		}
		default: {			
			i++;
		
		}

	}
		

	i = 5;
	return;
}