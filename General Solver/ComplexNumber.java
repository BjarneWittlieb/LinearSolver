package gen_solve;

public class ComplexNumber implements Fieldable {

	private final double re;
	private final double im;

	public ComplexNumber(double r, double i) {
		re = r;
		im = i;
	}

	@Override
	public Fieldable add(Fieldable other) {
		if (!other.getClass().equals(getClass())) {
			throw new IllegalArgumentException(
					"Passed argumant should be of type ComplexNumber but was of type " + other.getClass().getName());
		}
		ComplexNumber cmplx = (ComplexNumber) other;
		return new ComplexNumber(this.re + cmplx.re, this.im + cmplx.im);
	}

	@Override
	public Fieldable subtract(Fieldable other) {
		if (!other.getClass().equals(getClass())) {
			throw new IllegalArgumentException(
					"Passed argumant should be of type ComplexNumber but was of type " + other.getClass().getName());
		}
		ComplexNumber cmplx = (ComplexNumber) other;
		return new ComplexNumber(this.re - cmplx.re, this.im - cmplx.im);
	}

	@Override
	public Fieldable multiply(Fieldable other) {
		if (!other.getClass().equals(getClass())) {
			throw new IllegalArgumentException(
					"Passed argumant should be of type ComplexNumber but was of type " + other.getClass().getName());
		}
		ComplexNumber cmplx = (ComplexNumber) other;
		double x = this.re * cmplx.re - this.im * cmplx.im;
		double y = this.re * cmplx.re + this.im * cmplx.im;
		return new ComplexNumber(x, y);
	}

	@Override
	public Fieldable divide(Fieldable other) {
		if (!other.getClass().equals(getClass())) {
			throw new IllegalArgumentException(
					"Passed argumant should be of type ComplexNumber but was of type " + other.getClass().getName());
		}
		ComplexNumber cmplx = (ComplexNumber) other;
		double tmp = cmplx.re * cmplx.re + cmplx.im * cmplx.im;
		double x = (this.re * cmplx.re + this.im * cmplx.im) / tmp;
		double y = (this.im * cmplx.re - this.re * cmplx.im) / tmp;
		return new ComplexNumber(x, y);
	}
	
	public Fieldable[] solveVandermonde(Fieldable[] x, Fieldable [] rhs) {
		for (int k = 0; k < x.length - 1; k++)
	    {
	        for (int i = k + 1; i < x.length; i++)
	        {
	            rhs[i] = (rhs[i].subtract(rhs[k])).divide(x[i].subtract(x[k]));
	        }
	    }
	    for (int xi = x.length - 2; xi >= 0; xi--)
	    {
	        for (int i = xi; i < x.length - 1; i++)
	        {
	            rhs[i] = rhs[i].subtract(x[xi].multiply(rhs[i + 1]));
	        }
	    }
	    return rhs;
	}

}
