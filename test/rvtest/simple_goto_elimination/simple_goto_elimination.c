int main() {
	int i = 0;
	
	label:
	i++;
	if (i == 9){
		return 1;
	}
	if (i > 0){
		goto label;
	}
	return 2;
}
