#include <ostream>
#include <tuple>
#include <type_traits>

template<typename T>
using void_t = void;

/*! \typedef serializable_t<T,O>
    \brief Type of any operator<< for T
*/
template <typename T, typename O>
using serializable_t =
    decltype(operator<<(std::declval<O>(), std::declval<T>()));

/* ! \class is_serializable<T>
     \brief Integral types always serializable
*/
template <typename T, typename = void>
struct is_serializable : std::is_integral<T> {};

/* ! \class is_serializable
     \brief true_type for T having operator<<
*/
template <typename T>
struct is_serializable<T, void_t<serializable_t<T, std::ostream>>>
    : std::true_type {};

/*! \typedef container_begin_t
    \brief Type of any method begin() of T
*/
template<typename T>
using container_begin_t = decltype(std::declval<T&>().begin());

/*! \typedef container_end_t
    \brief Type of any method end() of T
*/
template<typename T>
using container_end_t = decltype(std::declval<T&>().end());

/*! \class is_std_container<T>
    \brief Check inherits std::is_array<T>
*/
template <typename T, typename = void, typename = void, typename = void, typename = void>
struct is_std_container : std::is_array<T> {};

/*! \class is_std_container<T, typename T::iterator>
    \brief Checks that T has iterator type and
    begin(), end() methods defined.
*/
template <typename T>
struct is_std_container<T,
                        void_t<typename T::iterator>,
                        void_t<container_begin_t<T>>,
                        void_t<container_end_t<T>>> :
  std::true_type {};

template <typename T>
struct is_std_tuple;

template <typename T>
struct is_std_tuple<std::tuple<T>> :
  std::true_type {
  using el = T;
  constexpr static bool homogeneous { true };
};

/*! \class is_std_tuple<typename T, typename ... U>
    \brief Checks that T is std::tuple
*/
template <typename T, typename... U>
struct is_std_tuple<std::tuple<T, U...>> : std::true_type {
  using el = T;
  /*! \var homogeneous
      \brief true if all types of the tuple same
  */
  constexpr static bool homogeneous{
      std::is_same<el, typename is_std_tuple<std::tuple<U...>>::el>::value &&
      is_std_tuple<std::tuple<U...>>::homogeneous};
};

/*! \fn print_ip_address
    \brief Prints integral types
*/
template<class T>
std::enable_if_t<std::is_integral<T>::value> print_ip_address(std::ostream& os, const T& t) {
  unsigned size = sizeof(T);
  for(unsigned i = 0; i < size; ++i) {
    if(i)
      os << ".";
    os << static_cast<unsigned>((t >> ((size - i - 1) * 8)) & 0xFF);
  }
  os << std::endl;
}

/*! \fn print_ip_address
  \brief Prints T if it passes container check, but not serializable
*/
template<typename T>
std::enable_if_t<is_std_container<T>::value && !is_serializable<T>::value>
print_ip_address(std::ostream& os, const T& t) {
  os << __PRETTY_FUNCTION__ << std::endl;
  for(auto it = t.begin(); it != t.end(); ++it) {
    if(it != t.begin())
      os << ".";
    os << *it;
  }
  os << std::endl;
}

/*! \fn print_ip_address
    \brief Prints T if it passes container check and serializable
*/
template <typename T>
std::enable_if_t<is_std_container<T>::value && is_serializable<T>::value>
print_ip_address(std::ostream &os, const T &t) {
  os << __PRETTY_FUNCTION__ << std::endl;
  os << t << std::endl;
}

template <typename T, std::size_t... I>
void print_tuple(std::ostream &os, const T &t, std::index_sequence<I...>) {
  bool ok[sizeof...(I)] = {
      ((os << (I == 0 ? "" : ".") << std::get<I>(t)), true)...};
  (void)ok;
}

template <typename... Args>
void print_tuple(std::ostream &os, const std::tuple<Args...> &t) {
  print_tuple(os, t, std::index_sequence_for<Args...>{});
}

/*! \fn print_ip_address
    \brief Prints tuple if it is homogeneous, fails otherwise
*/
template<typename T>
std::enable_if_t<is_std_tuple<T>::homogeneous> print_ip_address(std::ostream& os, const T& t) {
  os << __PRETTY_FUNCTION__ << std::endl;
  print_tuple(os, t);
  os << std::endl;
}
