#pragma once

#include <type_traits>
#include <utility>

namespace aggr
{

namespace detail
{
    template<typename T , int Idx, typename StopRecursion>
    struct count_members;

    template<typename T , int Idx>
    struct count_members<T , Idx , ::std::false_type> : ::std::false_type
    {   };

    template<typename T , int NArgs>
    struct count_members<T , NArgs , ::std::true_type>
    {
        template<::std::size_t I>
        struct any_type
        {
            template<typename U>
            operator U&() const;

            template<typename U>
            operator U&&() const;
        };

        template <typename... V>
        static constexpr
        decltype( T { ::std::declval<V>()... } , ::std::true_type{} )
        is_it_possible( T* );

        template <typename... V>
        static constexpr std::false_type is_it_possible( ... );

        template<::std::size_t... Idx>
        static constexpr
        decltype( is_it_possible<decltype( any_type<Idx> { } )...>( nullptr ) )
        construct( ::std::index_sequence<Idx...> );

        using result = decltype( construct( ::std::make_index_sequence<NArgs>() ) );
        using type   = T;

        static constexpr ::std::size_t value = result::value +
                                               count_members<T , NArgs + 1 , result>::value;
    };
}

template<typename T>
using count_members = detail::count_members<T , 1 , ::std::true_type>;

template<typename T>
static constexpr ::std::size_t count_members_v = count_members<T>::value;

}
