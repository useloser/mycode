#include <iostream>
#include <cstring>
#include <vector>
#include <assert.h>
using namespace std;


namespace easy_string {
	class string {
		public:
			string(const char *s = "")
				: _str(new char[strlen(s) + 1]) {
				strcpy(_str, s);
			}

			~string() {
				delete[] _str;
				_str = nullptr;
			}

//		string(const string &s)
//			: _str(new char[strlen(s._str) + 1]) {
//			strcpy(_str, s._str);
//		}

			string(const string &s)
				: _str(nullptr) {
				string tmp(s._str);
				swap(_str, tmp._str);
			}

//		string &operator=(const string &s) {
//			if (this != &s) {
//				char *tmp = new char[strlen(s._str) + 1];
//				strcpy(tmp, s._str);
//				delete[] _str;
//				_str = tmp;
//			}
//			return *this;
//		}

			string &operator=(string s) {
				swap(_str, s._str);
				return *this;
			}

			size_t size() const {
				return strlen(_str);
			}

			bool empty() {
				return !size();
			}

			const char *c_str() const {
				return _str;
			}

			char &operator[](size_t i) {
				return _str[i];
			}

			const char &operator[](size_t i) const {
				return _str[i];
			}

			bool operator==(const string &s) {
				return strcmp(_str, s._str);
			}
			string &operator<(const string &s);


			friend ostream &operator<< (ostream &out, const string &s);
			friend istream &operator>> (istream &in, const string &s);

		private:
			char *_str;
	};

	ostream &operator<< (ostream &out, const string &s) {
		out << s._str;
		return out;
	}

	istream &operator>> (istream &in, const string &s) {
		in >> s._str;
		return in;
	}

	void test1() {
		const string s1("nb");
		string s2("a123b");
		string s3 = s2;
		cout << s1 << s2 << s3 << endl;
		cout << s1.size() << s1[1] << endl;
	}

	void test2() {
		string s1;
		cin >> s1;
		cout << s1.size() << s1.empty();
		cout << s1[0];
	}

}

namespace complete_string {
	class string {
		public:
			typedef char *iterator;

			iterator begin() {
				return _str;
			}

			iterator end() {
				return _str + _size;
			}

			// 默认构造和s("123")
			string(const char *s = "") {
				_size = strlen(s);
				_capacity = _size;
				_str = new char[_capacity + 1];
				strcpy(_str, s);
			}
			//析构 delete nullptr不会报错
			~string() {
				delete[] _str;
				_str = nullptr;
				_size = _capacity = 0;
			}

//		string(const string &s)
//			: _str(new char[strlen(s._str) + 1]) {
//			strcpy(_str, s._str);
//		}
			//现代写法
			string(const string &s)
				: _str(nullptr) {
				string tmp(s._str);
				swap(tmp);
			}

//		string &operator=(const string &s) {
//			if (this != &s) {
//				char *tmp = new char[strlen(s._str) + 1];
//				strcpy(tmp, s._str);
//				delete[] _str;
//				_str = tmp;
//			}
//			return *this;
//		}

			string &operator=(string s) {
				swap(s);
				return *this;
			}
			//三个交换
			void swap(string &s) {
				::swap(_str, s._str);
				::swap(_size, s._size);
				::swap(_capacity, s._capacity);
			}

			size_t size() const {
				return _size;
			}

			size_t capacity() const {
				return _capacity;
			}

			bool empty() {
				return !size();
			}

			const char *c_str() const {
				return _str;
			}

			char &operator[](size_t i) {
				assert(i < _size);
				return _str[i];
			}

			const char &operator[](size_t i) const {
				assert(i < _size);
				return _str[i];
			}

			void resize(size_t n, char ch = '\0') {
				if (n <= _size) {
					_str[n] = '\0';
					_size = n;
				} else {
					if (n > _capacity) {
						reserve(n);
					}

					for (size_t i = _size; i < n; ++i)
						_str[i] = ch;
					_str[n] = '\0';
					_size = n;
				}
			}

			void reserve(size_t n) {
				if (n > _capacity) {
					char *newstr = new char[n + 1];
					strcpy(newstr, _str);
					delete[] _str;
					_str = newstr;
					_capacity = n;
				}
			}

			string &push_back(char ch) {
				if (_size == _capacity) {
					size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
					reserve(newcapacity);
				}
				_str[_size] = ch;
				_str[++_size] = '\0';
				return *this;
			}

			string &append(const char *s) {
				size_t len = strlen(s);
				size_t newcapacity = _size + len;
				if (newcapacity > _capacity) {
					reserve(newcapacity);
				}
				strcpy(_str + _size, s);
				_size += len;
				return *this;
			}

			string &operator+=(char ch) {
				push_back(ch);
				return *this;
			}

			string &operator+=(const char *s) {
				append(s);
				return *this;
			}

			string &insert(size_t pos, char ch) {
				assert(pos <= _size);
				if (_size == _capacity) {
					size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
					reserve(newcapacity);
				}

				size_t end = _size;
				while (end > pos) {
					_str[end] = _str[end - 1];
					--end;
				}

				_str[pos] = ch;
				_str[++_size] = '\0';

				return *this;
			}

			string &insert(size_t pos, const char *s) {
				assert(pos <= _size);
				size_t len = strlen(s);
				size_t newcapacity = _size + len;
				if (newcapacity > _capacity) {
					reserve(newcapacity);
				}
				size_t end = _size;
				while (end > pos) { // pos =0时, 要防止end=0时--, 用>
					_str[end] = _str[end - 1];
					--end;
				}
				strncpy(_str + pos, s, len);
				_size += len;
				_str[_size] = '\0';
				return *this;
			}

			void erase(size_t pos, size_t len = npos) {
				assert(pos < _size);
				if (len >= _size - pos) {
					_str[pos] = '\0';
					_size = pos;
				} else {
					size_t end = pos + len;
					while (end <= _size) {
						_str[end - len] = _str[end];
						++end;
					}
					_size -= len;
				}
			}
			size_t find(char ch, size_t pos = 0) {
				for (size_t i = pos; i < _size; i++) {
					if (_str[i] == ch)
						return i;
				}
				return npos;
			}
			size_t find(const char *s, size_t pos = 0) {
				char *p = strstr(_str, s);
				if (p) {
					return p - _str;
				} else {
					return npos;
				}
			}

			bool operator==(const string &s) {
				return (strcmp(_str, s._str) == 0);
			}
			bool operator<(const string &s) {
				return (strcmp(_str, s._str) == 0);
			}
			bool operator<=(const string &s) {
				return *this < s || *this == s;
			}
			bool operator>(const string &s) {
				return !(*this <= s);
			}
			bool operator>=(const string &s) {
				return !(*this < s);
			}
			bool operator!=(const string &s) {
				return !(*this == s);
			}
			friend ostream &operator<< (ostream &out, const string &s);
			friend istream &operator>> (istream &in, string &s);

		private:
			char *_str;
			size_t _size;
			size_t _capacity;

			static size_t npos;
	};

	size_t string::npos = -1;
	ostream &operator<< (ostream &out, const string &s) {
		for (size_t i = 0; i < s.size(); ++i)
			out << s[i];
		return out;
	}

	istream &operator>> (istream &in, string &s) {
//		in >> s._str;
		s.resize(0);
		while (1) {
			char ch;
			ch = in.get();
			if (ch == ' ' || ch == '\n') {
				break;
			} else {
				s += ch;
			}
		}
		return in;
	}

	void test1() {
		const string s1("nb");
		string s2("a123b");
		string s3 = s2;
		cout << s1 << s2 << s3 << endl;
		cout << s1.size() << s1[1] << endl;
	}

	void test2() {
		string s1;
		cin >> s1;
		cout << s1 << endl;
		cin >> s1;
		cout << s1;
	}

	void test3() {
		string s1("12345");
		for (size_t i = 0; i < s1.size(); i++) {
			cout << s1[i];
		}
		cout << endl;
		string::iterator it = s1.begin();
		while (it != s1.end()) {
			*it -= 1;
			cout << *it;
			++it;
		}
		cout << endl;
		for (auto e : s1) {
			cout << e;
		}
	}

	void test4() {
		string s1("12345");
		s1.push_back('1').append("666");
		cout << s1 << endl;
		s1.insert(0, '1');
		s1 += "777";
		cout << s1 << endl;
	}

	void test5() {
		string s1("abcdef");
		s1.resize(10, '6');
		cout << s1 << endl;
		s1.resize(3);
		cout << s1;
	}
}

int main() {
	complete_string::test2();
	return 0;
}