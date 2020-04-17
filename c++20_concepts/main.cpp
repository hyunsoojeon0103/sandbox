/*
    HJ2509
    Hyun Soo Jeon
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>
#include <ctime>
#include <algorithm>
//#include <concepts>

template<typename T> using Value_type = typename T::value_type;
template<typename T> using Iterator_of = typename T::iterator;

template <typename T, typename U>
concept SameHelper = std::is_same_v<T,U>;

template <typename T, typename U>
concept Same_type = SameHelper<T,U> && SameHelper<U,T>;

template <typename T>
concept Less_than_comparable = requires (T a, T b)
{
    { a < b } -> bool;
    { b < a } -> bool;
};

template<typename T, typename U>
concept Equality_comparable = requires(T a, U b) 
{
    { a == b } -> bool;
    { a != b } -> bool;
    { b == a } -> bool;
    { b != a } -> bool;
    { a == a } -> bool;
    { b == b } -> bool;
};

template <typename T> 
concept Input_iterator = 
    Equality_comparable<Value_type<T>,Value_type<T>> &&
    std::is_copy_constructible<T>::value && 
    std::is_copy_assignable<T>::value && 
    std::is_destructible<T>::value && 
    std::is_swappable<T>::value && requires (T t)
    {
        typename std::iterator_traits<T>::value_type;
        typename std::iterator_traits<T>::difference_type;
        typename std::iterator_traits<T>::pointer;
        typename std::iterator_traits<T>::reference;
        typename std::iterator_traits<T>::iterator_category;
        { ++t } -> T&;
        { *t } -> Value_type<T>;
        { *t++ } -> Value_type<T>;
    };

template <typename T>
concept Random_access_iterator = requires(T t, T u)
{
    { --t } -> T&;
    { ++t } -> T&;
    { t++ } -> T;
    { t-- } -> T;
    { *t-- } -> std::iterator_traits<T>::reference;
    { *t++ } -> std::iterator_traits<T>::reference;
    { t > u } -> bool;
    { t < u } -> bool;
    { t >= u } -> bool;
    { t <= u } -> bool;
    typename std::iterator_traits<T>::value_type;
    typename std::iterator_traits<T>::difference_type;
    typename std::iterator_traits<T>::reference;
    requires Input_iterator<T>;
    requires std::is_default_constructible<T>::value;
};

template <typename T>
concept Movable = 
    std::is_object<T>::value && 
    std::is_move_constructible<T>::value && 
    std::is_assignable<T&, T>::value &&
    std::is_swappable<T>::value;

template <typename T>
concept Boolean = Movable<std::remove_cvref_t<T>> && requires(const std::remove_reference_t<T>& b1, const std::remove_reference_t<T>& b2, const bool a)
{
    { b1 } -> std::is_convertible<const std::remove_reference_t<T>&, bool>::value;
    { !b1 } -> std::is_convertible<const std::remove_reference_t<T>&, bool>::value;
    { b1 && b2 } -> Same_type<bool>; 
    { b1 && a } -> Same_type<bool>; 
    { b1 || b2 } -> Same_type<bool>; 
    { b1 || a } -> Same_type<bool>; 
    { a || b2 } -> Same_type<bool>; 
    { b1 == a } -> bool;
    { a == b2 } -> bool;
    { b1 != b2 } -> bool;
    { b1 != a } -> bool;
    { a != b2 } -> bool;
};

template <typename T>
concept Sequence = requires(T t)
{
    typename Value_type<T>;
    typename Iterator_of<T>;
    { begin(t) }-> Iterator_of<T>;
    { end(t) }-> Iterator_of<T>;
    requires Input_iterator<Iterator_of<T>>;
    requires Same_type<Value_type<T>, Value_type<Iterator_of<T>>>;
};

template <typename T>
concept Sortable = Sequence<T> && Less_than_comparable<Value_type<T>> && Random_access_iterator<Iterator_of<T>>;

template <typename T, class... Args>
concept bool Predicate = std::is_invocable<T(), Args...>::value;// && Boolean<std::invoke_result<T, Args...>::type>;

template <typename S, typename T> requires Sequence<S> && Equality_comparable<Value_type<S>,T>
Iterator_of<S> myfind(S& seq, const T& value)
{
    return std::find(seq.begin(),seq.end(),value);
}

template <typename S, typename P> requires Sequence<S> && Predicate<P>
Iterator_of<S> myfindIf(S& seq, P predicate)
{
    return std::find_if(seq.begin(),seq.end(),predicate);
}

template <Sortable S, typename P = std::less<>> requires Predicate<P>  
void mysort(S& s, Predicate pred = P())
{
    std::sort(s.begin(),s.end(),pred);
}

template <Sequence Seq>
void foo(Seq& s)
{
    std::cout << "Foo!\n";
    return;
}

int randGene(const int low, const int high)
{
    return rand() % (high - low + 1) + low;
}
void display(const std::vector<int>& vect)
{
    std::for_each(vect.begin(),vect.end(),[](const int x){std::cout << x << ' ';});
    std::cout << '\n';
}
// __referencebale
// _Equality_comparable what are we checking for?_
//concept bool
//range
int main()
{
    srand((unsigned)time(NULL));

    const int SIZE = 100;

    auto comp = [](const int x, const int y){return x < y;};
    auto isOdd = [](const int x){return x % 2 != 0;};
    auto isEven = [](const int x){return x % 2 == 0;};

    /* Populate the vect */
    std::vector<int> vect;
    for(int i = 0; i < SIZE; ++i)
        vect.push_back(randGene(0,SIZE * 2));
  
    std::cout << "Before sorting\n";
    display(vect);

    /* mysort wraps std::sort */
    mysort(vect,comp);

    std::cout << "\nAfter sorting\n";
    display(vect);

    int target = randGene(0,SIZE * 2);

    /* myfind wraps std::find */
    std::cout << "\nSearching for " << target << '\n';
    auto it = myfind(vect,target);
    if(it != vect.end())
        std::cout << *it << " found\n";
    else
        std::cout << target << " cannot be found\n";
    

    /* myfindIf wrap std::find_if */
    std::cout << "\nSearching for the first odd number\n";
    it = myfindIf(vect,isOdd); // odd number
    if(it != vect.end())
        std::cout << *it << " is the first odd number\n";
    else
        std::cout << "No odd number can be found\n"; 

    std::cout << "\nSearching for the first even number\n";
    it = myfindIf(vect,isEven); // even number
    if(it != vect.end())
        std::cout << *it << " is the first even number\n";
    else
        std::cout << "No even number can be found\n"; 

    return 0;
}
