class GlobalState {
 public:
  static GlobalState& instance() {
    static GlobalState* instance = new GlobalState();
    return *instance;
  }

 private:
  GlobalState() {}
};