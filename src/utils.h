template <typename T>
inline T factorial(T n) {
   return (!n) ? 1 : n * factorial(n - 1); 
}
