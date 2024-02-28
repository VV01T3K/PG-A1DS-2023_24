class ExampleClass {
   public:
    ExampleClass() : value(0) {}                    // Default constructor
    explicit ExampleClass(int val) : value(val) {}  // Parameterized constructor

    int getValue() const { return value; }   // Getter
    void setValue(int val) { value = val; }  // Setter

   private:
    int value;
};