using Remez
setprecision(2000)

for sine in[true, false]
  for relative in[true, false]
    for degree in 0 : 16
      filename = "outfiles/"*(sine ? "" : "co")*"sine-"*lpad(convert(Any,degree), convert(Integer,2), string(0))*(relative ? "-relative.txt" : "-absolute.txt")
      println("Computing: "*(sine ? "S" : "Cos")*"ine, "*(relative ? "relative" : "absolute")*" error, degree $degree. -> $filename")
      if sine
        out = ratfn_minimax((x) -> sin(sqrt(x))/(sqrt(x)), (BigFloat(1e-318), BigFloat(pi*pi/4.)), degree, 0, (relative ? (x, y) -> 1. /y : (x, y) -> sqrt(x)))
      else
        out = ratfn_minimax((x) -> cos(sqrt(x)), (BigFloat(1e-318), BigFloat(pi*pi/4.)), degree, 0, (relative ? (x, y) -> 1. /y : (x, y) -> 1.))
      end

      open(filename, "w") do f
        write(f, string(out))
      end
    end
  end
end
