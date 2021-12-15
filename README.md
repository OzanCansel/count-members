# count-members

Counts the members of an aggregate type.

- C++17
- Tested on GCC

``` c++

#include <iostream>
#include "count_members.hpp"

struct a_type
{
  int a;
  int b;
  int c;
};

int main()
{
  std::cout << "a_type has "
            << aggr::count_members_v<a_type>
            << " members."
            << std::endl;
}

```

## LICENSE
[MIT](https://raw.githubusercontent.com/OzanCansel/count-members/master/LICENSE)
