"""@package plotutils
Convenient plotting functions using Matplotlib.
"""

#! /Library/Frameworks/Python.framework/Versions/2.7/bin/python

import numpy as np
import matplotlib.pyplot as plt
from sklearn.neighbors import KernelDensity
from sklearn.grid_search import GridSearchCV


def SilvermanBandwidth(X):
    """Compute bandwidth for a Gaussian KDE with Silverman's rule.

    Parameters
    ----------
    X: Numpy array with shape (n, 1). This is the same as
       scikit-learn's convention for a single feature over
       all records.

    Returns
    -------
    Real number: The smoothing bandwidth of the input determined
                 using Silverman's rule.
    """
    return 1.06 * np.std(X) * (len(X) ** (-0.2))


def FreedmanDiaconisBinwidth(x):
    """Compute histogram binwidth using Freedman-Diaconis' rule.

    Parameters
    ----------
    x: Numpy array with shape (n, ).

    Returns
    -------
    Integer: The number of bins determined using Freedman-Diaconis'
             rule. The result is rounded down to the nearest integer.
    """
    hist_range = x.max() - x.min()
    IQR = np.percentile(x, 75) - np.percentile(x, 25)
    return int(hist_range / (2 * IQR * (len(x) ** (-1.0 / 3))))


def ExtractArrayByCategory(arr, varname, catname, cat_idx):
    """Extract a column from structured array for a specified category.

    Given a structured array, extract a specific column for a specific
    category of records. For example, return feature x for records that
    belong to category c.

    Parameters
    ----------
    arr: Numpy structured array.
    varname: Name of the column to extract.
    catname: Name of the column indicating the category of each record.
    cat_idx: The specific category of interest.

    Returns
    -------
    Numpy array: Shape is (n, ), where n is the number of records
                 belonging to the category of interest.
    """
    x, c = arr[varname], arr[catname]
    return x[c == cat_idx]


def GroupCategories(x, c, groups=None, labels=None, exclude=[]):
    """Get numpy arrays based on specified groupings of categories.

    Given numpy array x of elements and another numpy array c whose
    elements are the categories x belongs to. Return a list of
    numpy arrays whose elements are those in x belonging in the same
    group.

    Parameters
    ----------
    x: Numpy array with shape (n, ) to project.
    c: Numpy array with shape (n, ) whose elements are the categories.
    groups: dictionary whose keys are integers and values are lists
            whose elements are categories that should be grouped in
            one larger category.
    labels: dictionary of more descriptive names. Its keys are the same
            as those in groups and values are strings.
    exclude: List of groups to exclude from the result. Each list element
             corresponds to a key in groups.

    Returns
    -------
    list: Each element is a numpy array corresponding to x projected into
          the prespecified groups.
    list: Labels for each numpy array element returned.
    """

    if not groups:
        groups = dict([(i, [i]) for i in map(int, np.unique(c))])

    if not labels:
        labels = dict([(i, str(i)) for i in groups.keys()])

    x_i, label_i = [], []
    for g in groups.items():
        if g[0] not in exclude:
            x_i.append(x[reduce(np.logical_or,
                                map(np.equal, [c] * len(g[1]), g[1]))])
            label_i.append(labels[g[0]])

    return x_i, label_i


def ApplySelectionCuts(x, selection_dict):
    """Apply cuts on a structure array x.

    Given a structure array x and selection dictionary with the format
    { 'varname': (lower, upper) ... }, return another structured array
    that is appropriately filtered. lower and upper are the lower and
    upper limits a record can have for variable 'varname'.

    Parameters
    ----------
    x: Numpy array structured array.
    c: Dictionary of selction cuts.

    Returns
    -------
    Numpy structured array: Each element is a numpy array that passes
                            conditions imposed by selection_dict.
    """

    logic = np.ones(len(x), dtype=bool)
    for c in selection_dict.items():
        varname, lower, upper = c[0], c[1][0], c[1][1]
        if lower:
            logic = np.logical_and(logic, x[varname] > lower)
        if upper:
            logic = np.logical_and(logic, x[varname] < upper)

    return x[logic]


def StackByCategory(arr, varname, catname, wgtname=None,
                    cat_groups=None, cat_labels=None, cat_exclude=[],
                    cut_dict=None,
                    ax=None, xlim=None, **kwargs):
    """Make a stacked histogram grouped by a specific category.

    Given a structured array, make a stacked histogram of a some
    variable grouped by some category. For example, make a stacked
    histogram of height grouped by species type.

    Parameters
    ----------
    arr: Numpy structured array.

    varname: Name of the column to histogram.

    catname: Name of the column with the categories to group by.

    wgtname: Name of the column containing observation weights.
             Defaults to weight 1 for all records.

    cut_dict: Dictionary of selection cuts.

    cat_groups: Dictionary that group finer categories into larger ones.
                Keys are integers and values are list of finer category
                indices.

    cat_labels: Dictionary that provides a mapping between specific
                cat_group category indices with a more descriptive label.

    cat_exclude: List of cat_group category indices to exclude.

    ax: Plotting axis to draw on. Defaults to pyplot.gca().

    **kwargs: **kwargs for pyplot.hist().

    Returns
    -------
    (counts, bins, patches): Same as pyplot.hist().
    """

    if not ax:
        ax = plt.gca()

    if xlim:
        ax.set_xlim(xlim)

    if cut_dict:
        arr = ApplySelectionCuts(arr, cut_dict)

    x, c = arr[varname], arr[catname]
    x_i, labels = GroupCategories(x, c, cat_groups, cat_labels, cat_exclude)

    w_i = None
    if wgtname:
        w = arr[wgtname]
        w_i, labels = GroupCategories(w, c,
                                      cat_groups, cat_labels, cat_exclude)

    counts, bins, patches = ax.hist(x_i, weights=w_i,
                                    stacked=True, label=labels,
                                    histtype='stepfilled', alpha=0.7,
                                    linewidth=0,
                                    **kwargs)

    ax.legend()
    ax.set_xlabel(varname)
    ax.set_ylabel('Stacked Counts')

    return counts, bins, patches


def NormByCategory(arr, varname, catname,
                   exclude=[], cat_dict=None,
                   ax=None,
                   **kwargs):
    """Make a normed histograms grouped by a specific category.

    Obsolete. Prefer using KdeByCategory to study densities.
    """

    if not ax:
        ax = plt.gca()

    x, c = arr[varname], arr[catname]

    cat = []
    for i in map(int, np.unique(c)):
        if i not in exclude:
            cat.append(i)

    x_i = [x[c == i] for i in cat]

    labels = []
    if cat_dict:
        labels = [cat_dict[i] for i in cat]
    else:
        labels = map(str, map(int, cat))

    counts, bins, patches = ax.hist(x_i, normed=True, label=labels,
                                    histtype='stepfilled',
                                    alpha=0.7, linewidth=0,
                                    **kwargs)

    ax.legend()
    ax.set_xlabel(varname)
    ax.set_ylabel('Probability Density')

    return counts, bins, patches


def KdeByCategory(arr, varname, catname,
                  cat_groups=None, cat_labels=None, cat_exclude=[],
                  cut_dict=None,
                  legend_loc=1, legend_size=12,
                  ax=None, xlim=None):
    """Estimate and plot probability densities grouped by category.

    Given a structured array, estimate and plot probability densities
    for a specific variable grouped by some category.

    The densities are estiamted using Gaussian kernels with
    Silverman's rule for bandwidth selection.

    Parameters
    ----------
    arr: Numpy structured array.

    varname: Name of the column to estimate the probability density.

    catname: Name of the column with the categories to group by.

    cat_groups: Dictionary that group finer categories into larger ones.
                Keys are integers and values are list of finer category
                indices.

    cat_labels: Dictionary that provides a mapping between specific
                cat_group category indices with a more descriptive label.

    cat_exclude: List of cat_group category indices to exclude.

    cut_dict: Dictionary of selection cuts.

    ax: Plotting axis to draw on. Defaults to pyplot.gca().
    """

    if not ax:
        ax = plt.gca()

    if xlim:
        ax.set_xlim(xlim)

    if cut_dict:
        arr = ApplySelectionCuts(arr, cut_dict)

    x, c = arr[varname], arr[catname]
    x_i, labels = GroupCategories(x, c, cat_groups, cat_labels, cat_exclude)

    kde_i = []
    for x in x_i:
        X = x[:, np.newaxis]
        kde_params = {'kernel': 'gaussian',
                      'bandwidth': SilvermanBandwidth(X),
                      'rtol': 1e-4}
        kde = KernelDensity(**kde_params).fit(X)
        kde_i.append(kde)

    X_plot = np.linspace(x.min(), x.max(), 1000)[:, np.newaxis]
    for kde, lab in zip(kde_i, labels):
        log_dens = kde.score_samples(X_plot)
        ax.plot(X_plot, np.exp(log_dens), linewidth=2, alpha=0.5, label=lab)

    ax.legend(loc=legend_loc, prop={'size': legend_size})
    ax.set_xlabel(varname)
    ax.set_ylabel('Probability Density')

    return


# Overlay histogram with Gaussian kernel density estimators.
def KdeOverHist(arr, varname, catname, cat_idx, cat_dict=None,
                silverman=True, bandwidths=[], cv=False, bins=None,
                legend_loc=1, legend_size=12,
                ax=None):
    """Plot estimated probability density overlayed on a histogram.

    Given a structured array, a specific variable, and a specific
    category, estimate and plot probability densities using various
    techniques and overlay the results on a histogram.

    The densities are estimated using Gaussian kernels. The various
    techniques are really various bandwidth selection techniques.

    Parameters
    ----------
    arr: Numpy structured array.

    varname: Name of the column to plot.

    catname: Name of the column with the category information.

    cat_idx: The specific index of the category of interest.

    cat_dict: Dictionary that provides a mapping between specific
              category indices with a more descriptive label.

    silverman: Use Silverman's rule to estimate the bandwidth.

    bandwidths: List of bandwidths to try. Manual "dial-in"s.

    cv: Use cross validation to estimate the bandwidth. See
        source for the details/parameters.

    bins: Number of bins for the histogram. If left alone,
          this defaults to the Freedman-Diaconis rule.

    ax: Plotting axis to draw on. Defaults to pyplot.gca().
    """

    if not ax:
        ax = plt.gca()

    x, c = arr[varname], arr[catname]
    x = x[c == cat_idx]

    X = x[:, np.newaxis]

    labels, kdes = [], []

    # User specified bandwidths
    for bw in bandwidths:
        params = {'kernel': 'gaussian', 'bandwidth': bw, 'rtol': 1e-4}
        kdes.append(KernelDensity(**params).fit(X))
        labels.append('h = {0}'.format(bw))

    # Silverman bandwidth
    if silverman:
        params = {'kernel': 'gaussian',
                  'bandwidth': SilvermanBandwidth(X),
                  'rtol': 1e-4}
        kdes.append(KernelDensity(**params).fit(X))
        labels.append(
            'h={0} (SR)'.format(
                round(SilvermanBandwidth(X), 2)))

    # Cross Validation bandwidth
    if cv:
        grid = GridSearchCV(KernelDensity(),
                            {'bandwidth': np.linspace(
                                SilvermanBandwidth(X) / 2.0,
                                SilvermanBandwidth(X) * 2.0,
                                30),
                             'rtol': [1e-4]},
                            cv=20)
        grid.fit(X)
        params = {'kernel': 'gaussian',
                  'bandwidth': grid.best_params_['bandwidth'],
                  'rtol': 1e-4}
        kdes.append(KernelDensity(**params).fit(X))
        labels.append(
            'h={0} (CV)'.format(
                round(grid.best_params_['bandwidth'], 2)))

    # Plot KDE results
    X_plot = np.linspace(x.min(), x.max(), 1000)[:, np.newaxis]
    for kde, lab in zip(kdes, labels):
        log_dens = kde.score_samples(X_plot)
        ax.plot(X_plot, np.exp(log_dens), linewidth=2, alpha=0.5, label=lab)

    # Plot histogram
    hist_label = 'B = {0}'
    if not bins:
        bins = FreedmanDiaconisBinwidth(x)
        hist_label += ' (FD)'
    hist_label = hist_label.format(bins)

    ax.hist(x, bins=bins, histtype='stepfilled',
            alpha=0.3, normed=True, fc='gray',
            linewidth=0,
            label=hist_label)

    # Legend
    ax.legend(loc=legend_loc, prop={'size': legend_size})

    # Plot format
    if cat_dict:
        ax.set_title('{0} category'.format(cat_dict[cat_idx]))
    else:
        ax.set_title('{0} category'.format(cat_idx))

    ax.set_xlabel(varname)
    ax.set_ylabel('Probability Density')

    return


if __name__ == '__main__':

    fig = plt.figure()
    #x = np.array([1, 1, 1, 3, 3, 4, 4, 4, 4, 4, 2, 2, 2, 2])
    #StackByCategory(x, bins=4, histtype='stepfilled', alpha=0.4)
    #plt.hist(x)
