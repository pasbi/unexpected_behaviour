/*
 The following code won't compile, as the compiler fails to resolve `foo(lib::A, lib::A)` (III).
 It is kind of natural, as (III) is in namespace `app` and the required `foo` is in another
 (default) namespace while there is another (not fitting) `foo` in the very `app` namespace.

 There are many solutions to make the code work, though:
  A) define `foo(lib::A, lib::A)` in namespace `lib`. ADL will lookup the correct namespace
    (`lib`), and uses `lib::foo` eventually.
  B) tell the compiler to use `foo` in default-namespace explicitely, i.e., replace `foo` in (III)
    with `::foo`.
  C) do not declare `foo(app::B, app::B)` before requiring `foo(lib::A, lib::A)`, i.e., remove
    (II) or move it after (III)
  D) declare `foo(app::B, app::B)` outside of namespace `app`. This of course also works even if
    (III) comes after (II) (that implies to reopen namespace `app` in order to declare (III).)

  Conclusion: I guess `::foo(lib::A, lib::A)` is not considered because `app::foo(app::B, app::B)`
  seems more suitable (same namespace). While this argument is still valid for case (A), it will
  compile thanks to ADL as `lib::foo(lib::A, lib::A)` is in the same namespace as its arguments.
  That's not the case in the plain example, hence ADL cannot be applied and the required
  `::foo(lib::A, lib::A)` is not considered.

  tested with gcc version 8.2.1 20180831 (GCC) and clang version 7.0.0
 */

namespace lib {
class A {};
}
lib::A foo(lib::A lhs, lib::A rhs) { return lhs; }        // (I)

namespace app {
class B {};
app::B foo(app::B lhs, app::B rhs) { return lhs; }        // (II)
lib::A bar() { return foo(lib::A(), lib::A()); }          // (III)
}

int main (int argc, char *argv[])
{
}
