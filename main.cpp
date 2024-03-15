#include <iostream>
using namespace std;

class Stack {
   private:
    char* stack;
    int size;
    int wskaznik = 0;

   public:
    int count = 0;
    bool overflow = false;
    Stack(int new_size) {
        size = new_size;
        stack = new char[new_size]{0};
    };
    ~Stack() { delete[] stack; };
    void push(char c) {
        if (wskaznik + 1 > size) overflow = true;
        stack[wskaznik++] = c;
        count++;
    };

    char pop() {
        count--;
        return stack[wskaznik-- - 1];
    };

    char peek() { return stack[wskaznik - 1]; };

    void print() {
        for (int i = 0; i < wskaznik; i++) {
            cout << stack[i] << " ";
        }
        cout << endl;
    };
};

char getznak(char c) {
    switch (c) {
        case '(':
            return ')';
            break;
        case '{':
            return '}';
            break;
        case '<':
            return '>';
            break;
        case '[':
            return ']';
            break;
        case ')':
            return '(';
            break;
        case '}':
            return '{';
            break;
        case '>':
            return '<';
            break;
        case ']':
            return '[';
            break;
        default:
            return '0';
            break;
    }
}

int main() {
    char c;
    int n;
    cin >> n;
    Stack stack(n);
    bool stop = false;
    int znak_nr = -1;
    while (scanf("%c", &c) == 1) {
        if (stop) break;
        if (stack.overflow) {
            cout << "Stack Overflow\n";
            break;
        }
        znak_nr++;
        switch (c) {
            case '[':
            case '<':
            case '(':
            case '{':
                stack.push(c);
                break;
            case ']':
            case '>':
            case ')':
            case '}':
                if (stack.count <= 0) {
                    cout << "error:" << znak_nr
                         << ": expected statement before '" << c << "' token\n";
                    stop = true;
                    break;
                } else if (stack.peek() != getznak(c)) {
                    cout << "error:" << znak_nr << ": expected '"
                         << getznak(stack.peek()) << "' before '" << c
                         << "' token\n";
                    stop = true;
                    break;
                }
                stack.pop();
                break;
            default:
                break;
        }
    }
    if (stack.count > 0) {
        cout << "error:" << znak_nr + 2 << ": expected statement before '"
             << getznak(stack.peek()) << "' token\n";
        // cout << "error:" << znak_nr << ": expected '" <<
        // getznak(stack.peek())
        //      << "' before end of file\n";
    } else if (!stack.overflow && !stop)
        cout << "ok\n";
}