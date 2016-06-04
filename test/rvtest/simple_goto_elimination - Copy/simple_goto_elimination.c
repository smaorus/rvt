void move(int n)
{
	int i, j = 0;

    while(i < 5000){

		i++;
		alabel:
			j++;
		break;
		if (j == 0){
			j--;
			while (j == 0){
				if (j == 0){
					break;
				}
			}
			continue;
		}
		
		if (i == 5){
			goto alabel;
		}
	}
}


int main() {
	move(7);
	return 0;
}
