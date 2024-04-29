-- To compile "ghc [file name] -o [output name]"
-- pretty much the same as GNU C compile argument instead of "gcc", haskell use "ghc"
-- since Haskell Language Compiler literally based on GNU C

-- Domain of a Variable [D]   
-- x is a value with domain of Integer [Z], has discrete value with range (-∞, +∞)  
-- or x = {-∞, ..., -2, -1, 0, 1, 2, ..., ∞} (with no in-between)

-- Dx = {x | x ∈ Z}   or   x -> Z
-- [Variable] :: Domain             (Variable declaration)
-- [variable] = (value)             (Value Assignment, Domain will automatically assigned if not specified beforehand)
-- [variable] :: Domain = (value)   {Variable Initialization}
x :: Integer
x = 200


-- List of Domain
-- Integer  [Z] {-∞, ..., -2, -1, 0, 1, 2, ..., +∞} | Integer
-- Real     [ℝ] {-∞, ..., +∞}                       | Double

-- Limited range Domain
-- int       {D | D ∈ Z, (-2^63 + 1) ≤ D ≤ 2^63} or with range  D ⊂ [(-2^63 + 1), 2^63]

-- Special Domain
-- Boolean  [ ] {false, true}                       | Bool

real_numbers :: Double
real_numbers = 12.5 * 21.3829

limited_integer :: Int = 34500
-- limited_integer = 65200000000000000000000  (error: Out of Range)

true_integer :: Integer
true_integer = 65200000000000000000000000000000000    -- (ok)

-- Automatic Domain Assignment if not specified beforehand (D ⊂ Bool)
booleans = True
-- booleans = 0     (error: undefined domain)
-- booleans = 420   (error: undefined domain)


-- ========================== FUNCTION =====================================
-- Haskell is a functional Language resembling mathematics as close as possible
-- Before defining a function, we need to define its domain and range

-- y = (def)  {x | x ∈ Z} ; {y | y ∈ Z} ;
-- f(x) | x -> y
-- Df(x) | Dx -> Dy

-- Function Definition
-- Domain and Range Declaration     [Funcion name] :: Domain -> Range / Co-Domain
-- Function Definition              [Function name](variable) = (Expression)

-- function f(x) has domain of [integer] and return [integer] as co-domain 
-- f(x) has range of [ Z ]

-- f(x) = (...) {x,f(x) | x,f(x) ∈ Z}

-- Domain
f :: Integer -> Integer

-- Definition
-- f(x) = x * x
-- or
f x = x * x

-- Multivariable Function       [Function name] :: Domain 1 -> domain 2 -> domain ... -> domain n-th variable -> co-domain / return domain
--                              [Function name] var1 var2 ... varn-th = (...)

g :: Integer -> Integer -> Integer
g x y = x * y 

-- Function Composition (f o g)(x)
-- f(x) = (...)  g(x) = (...)
-- f(g(x)) = g(...)(x)

-- When the variables not a literal value but instead a function in a function use () to call
-- f(f(x))

-- Multivariable with function composition (Complete Fundamental Function Declaration)
-- Domain                       [Function Name] :: (domain 1, domain 2, ..., domain n-th) -> co-Domain / Range
-- Definition                   [Function Name](var1, var2, ..., varn-th) = (...)


-- f(x, y, z) = (...) {x | x ∈ ℝ ; y | y ∈ ℝ ; z | y ∈ ℝ}
-- f(x, y, z) = (...) {x,y,z | x,y,z ∈ ℝ} {f(x) | f(x) ∈ ℝ}

-- Domain for the Displacement [ℝ] (Real Numbers)
displacement :: (Double, Double, Double) -> Double
displacement(acceleration, velocity, time) = (1/2 * (acceleration * time * time)) + (velocity * time)

acceleration :: Double
acceleration = 9.8

force :: Double -> Double
force(mass) = mass * acceleration

-- With Function Composition
work :: (Double, Double) -> Double
work(force, displacement) = force * displacement


energy :: Double = work(force(20), displacement(acceleration, 10, 2)) 



main :: IO()

main = print(displacement(0.12, 12, 9.8))




