#include <stdio.h>
#include <iostream>


/*Things I could improve:
	Maybe use a list of integers instead of a string. 
	This only works for multiplying two integers with same length + len = 2^k.
*/
using namespace std; 

//Given a, b --> str versions for integers, pads enough 0s to the 
//left so that len(a)==len(b)
void equalize_lengths(string& a, string& b){
	int diff = a.length()-b.length();
	string to_append (abs(diff), '0');

	if (diff > 0){
		to_append.append(b);
		b = to_append;

	} else if (diff < 0){
		to_append.append(a);
		a = to_append;
	}

	return;
}
//Reverses the string
void reverse_str(string& str){
	int n = str.length();
	for (int i = 0; i < n / 2; i++){
		swap(str[i], str[n - i - 1]);
	}
	return;
}

//addition of two strings representing integers.
string str_addition(string a, string b){
	char carry_ch='0';
	char new_bit_ch; 
	int new_bit;
	int i;


	if (a.length() != b.length()){
		equalize_lengths(a, b);

	}

	int length = a.length();

	string result (length+1, '0');

	for(i=length-1; i>=0; i--){
		new_bit = (a[i]-'0')+(b[i]-'0')+(carry_ch-'0');

		new_bit_ch = (new_bit%10)+'0';
		carry_ch = (new_bit/10)+'0';

		result[length-i-1] = new_bit_ch;
	}

	if(carry_ch != '0'){
		result[length] = carry_ch;
	} else {
		result = result.substr(0, length);
	}

	reverse_str(result);

	return result;


}

//not actually karatsuba, just recursive mult. Too lazy to think about str_subtraction
string karatsuba(string n1, string n2, int input_size){
	if(input_size==1){
		return to_string((n1[0]-'0')*(n2[0]-'0'));
	} else {
		int mid = input_size/2;

		string ac = karatsuba(n1.substr(0, mid), n2.substr(0, mid), input_size/2);
		string ad = karatsuba(n1.substr(0, mid), n2.substr(mid, mid), input_size/2);
		string bc = karatsuba(n1.substr(mid, mid), n2.substr(0, mid), input_size/2);
		string db = karatsuba(n1.substr(mid, mid), n2.substr(mid, mid), input_size/2);

		// need ac, ad, bc bd, (10^n/2*a+b)(10^n/2c+d)=10^n * ac + 10^(n/2)(ad + bc) + db
		string n_zeros (input_size, '0');
		string n_half_zeros (input_size/2, '0');

		ac.append(n_zeros);//10^n*ac
		string ad_plus_bc = str_addition(ad, bc);//ad+bc
		ad_plus_bc.append(n_half_zeros);//10^(n/2)*(ad+bc)


		return str_addition(ac, str_addition(ad_plus_bc, db));
	}
}

int main(){
	const int input_size = 64;

	string n1="3141592653589793238462643383279502884197169399375105820974944592";
	string n2="2718281828459045235360287471352662497757247093699959574966967627";
	//Correct from wolfram:
	//8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184
	//My output:
	//8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184

	string result = karatsuba(n1, n2, input_size);

	cout<<result<<endl;
	return 0;
}