#include <vector>

template <typename T>

// I probably didn't need to implement this, and maybe I shouldn't have done so
// using std::vector
class stack {
  private:
    std::vector<T> data;

  public:
    void push(T item) {
      data.push_back(item);
    }

    T pop() {
      T item = data.back();
      data.pop_back();
      return item;
    }

    T peek() {
      return data.back();
    }

    bool empty() {
      return data.empty();
    }

    int size() {
      return data.size();
    }
};