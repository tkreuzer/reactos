

using System.Runtime.Serialization;

namespace Test
{
    class Foo
    {
        public override bool Equals(object obj)
        {
            System.Boolean d;
            return base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public override string ToString()
        {
            return base.ToString();
        }
    }
}