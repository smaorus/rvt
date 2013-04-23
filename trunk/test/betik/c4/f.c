enum E_t { First = 1, Second};


int f(enum E_t);

int main() {
  enum E_t v = First;
  return f(v);
}


int f(enum E_t x) {
	switch(x) {
	case First: return f(Second);
	default: return 1;
	}
}


